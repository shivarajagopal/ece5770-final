using namespace std;
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <stdexcept>

/////////////////////////////////////////////////////////////////////////////////////////
// Aho-Corasick's algorithm, as explained in  http://dx.doi.org/10.1145/360825.360855  //
/////////////////////////////////////////////////////////////////////////////////////////

const int MAXS = 8361;    // Max number of states in the matching machine.
                        // Should be equal to the sum of the length of all keywords.

const int MAXC = 255; // Number of characters in the alphabet.

const int TERMS = 273;

int numTerms;

char out[MAXS][TERMS]; // Output for each state, as a bitwise mask.
               // Bit i in this mask is on if the keyword with index i appears when the
               // machine enters this state.

// Used internally in the algorithm.
int f[MAXS]; // Failure function
int g[MAXS][MAXC]; // Goto function, or -1 if fail.

// Builds the string matching machine.
// 
// words - Vector of keywords. The index of each keyword is important:
//         "out[state][i]" is 1 if we just found word[i] in the text.
// lowestChar - The lowest char in the alphabet. Defaults to 'a'.
// highestChar - The highest char in the alphabet. Defaults to 'z'.
//               "highestChar - lowestChar" must be <= MAXC, otherwise we will
//               access the g matrix outside its bounds and things will go wrong.
//
// Returns the number of states that the new machine has. 
// States are numbered 0 up to the return value - 1, inclusive.
int buildMatchingMachine(const vector<string> &words) {
		memset(out, 0, sizeof out);
    memset(f, -1, sizeof f);
    memset(g, -1, sizeof g);
    
    int states = 1; // Initially, we just have the 0 state
    int j;    
    for (int i = 0; i < words.size(); ++i) {
        const string &keyword = words[i];
        int currentState = 0;
        for (int j = 0; j < keyword.size(); ++j) {
            int c = keyword[j];
            if (g[currentState][c] == -1) { // Allocate a new node
                g[currentState][c] = states++;
            }
            currentState = g[currentState][c];
        }
        out[currentState][i] = 1; // There's a match of keywords[i] at node currentState.
    }
    
    // State 0 should have an outgoing edge for all characters.
    for (int c = 0; c < MAXC; ++c) {
        if (g[0][c] == -1) {
            g[0][c] = 0;
        }
    }

    // Now, let's build the failure function
    queue<int> q;
    for (int c = 0; c <= 0xff; ++c) {  // Iterate over every possible input
        // All nodes s of depth 1 have f[s] = 0
        if (g[0][c] != -1 and g[0][c] != 0) {
            f[g[0][c]] = 0;
            q.push(g[0][c]);
        }
    }
    while (q.size()) {
        int state = q.front();
        q.pop();
        for (int c = 0; c <= 0xff; ++c) {
            if (g[state][c] != -1) {
                int failure = f[state];
                while (g[failure][c] == -1) {
                    failure = f[failure];
                }
                failure = g[failure][c];
                f[g[state][c]] = failure;
								for (j = 0 ; j < TERMS ; ++j ) {
									if (out[failure][j]) out[g[state][c]][j] = 1;
								}
                q.push(g[state][c]);
            }
        }
    }

    return states;
}


// Print out the 3 arrays necessary to a file.
void outputArrays() {
		// Open file
		std::ofstream savefile("arrays.h");

		// Output g
    savefile << "int g[" << MAXS << "][" << MAXC << "] = {\n";
    for (int i = 0; i < MAXS-1; i++) {
        savefile << "\t{";
        for (int j = 0; j < MAXC-1; j++) {
            savefile <<  g[i][j] << ", ";
        }
        savefile << g[i][MAXC-1] << "},\n";
    }
    
    savefile << "\t{";
    for (int j = 0; j < MAXC-1; j++) {
        savefile <<  g[MAXS-1][j] << ", ";
    }
    savefile << g[MAXS-1][MAXC-1] << "}\n};\n\n";

		// Output f
    savefile << "int f[" << MAXS << "] = {\n\t";
    for (int i = 0; i < MAXS-1; i++) {
        savefile << f[i] << ", ";
    }
    savefile << f[MAXS-1] << "\n};\n\n";

		// Output out
    savefile << "char out[" << MAXS << "][" << TERMS << "] = {\n";
    for (int i = 0; i < MAXS-1; i++) {
				savefile << "\t{";
				for (int j=0; j < TERMS-1; j++) {
						savefile << +out[i][j] << ", ";
				}
        savefile << +out[i][TERMS-1] << "},\n";
    }

		savefile << "\t{";
		for (int j=0; j < TERMS-1; j++) {
			savefile << +out[MAXS-1][j] << ", ";
		}
    savefile << +out[MAXS-1][TERMS-1] << "}\n};\n\n";
		
		// Output number of terms
    savefile << "const int terms = " << numTerms << ";\n\n";

		// Close file
    savefile.close();

}

string hex_to_string(const string& input)
{
	  static const char* const lut = "0123456789ABCDEF";
		size_t len = input.length();
		if (len & 1) throw invalid_argument("odd length");
    string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)  {
			char a = input[i];
			const char* p = lower_bound(lut, lut + 16, a);
			if (*p != a) throw invalid_argument("not a hex digit");
			char b = input[i + 1];
			const char* q = lower_bound(lut, lut + 16, b);
			if (*q != b) throw invalid_argument("not a hex digit");
			output.push_back(((p - lut) << 4) | (q - lut));
		}
    return output;
}

// Build the AC matching machine from the given words
int ACbuild() {
    vector<string> keywords;
    int totalLength = 0;
		std::ifstream file("shellcode.txt");
		std::string str;
		while(std::getline(file, str)) {
			keywords.push_back(str);
		}
		std::ifstream hexFile("shellcodeHex.txt");
		while(std::getline(hexFile, str)) {
			keywords.push_back(hex_to_string(str));
		}
		for(int i=0; i < keywords.size(); i++){
			totalLength += keywords[i].length();
		}
		char earlyExit = 0;
    if (totalLength != MAXS) {
			cout << "Please set MAXS to " << totalLength << endl;
			earlyExit = 1;
		}
		numTerms = keywords.size();
		if (numTerms != TERMS) {
			cout << "Please set TERMS to " << numTerms << endl;
			earlyExit = 1;
		}
		if (earlyExit) return earlyExit;
    buildMatchingMachine(keywords);
    outputArrays();
		return 0;
}

int main(){
	int result = ACbuild();
	return result;
}

