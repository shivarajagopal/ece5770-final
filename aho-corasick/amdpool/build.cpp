using namespace std;
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <queue>

/////////////////////////////////////////////////////////////////////////////////////////
// Aho-Corasick's algorithm, as explained in  http://dx.doi.org/10.1145/360825.360855  //
/////////////////////////////////////////////////////////////////////////////////////////

const int MAXS = 16;    // Max number of states in the matching machine.
                        // Should be equal to the sum of the length of all keywords.

const int MAXC = 255; // Number of characters in the alphabet.

int numTerms;

int out[MAXS]; // Output for each state, as a bitwise mask.
               // Bit i in this mask is on if the keyword with index i appears when the
               // machine enters this state.

// Used internally in the algorithm.
int f[MAXS]; // Failure function
int g[MAXS][MAXC]; // Goto function, or -1 if fail.

// Builds the string matching machine.
// 
// words - Vector of keywords. The index of each keyword is important:
//         "out[state] & (1 << i)" is > 0 if we just found word[i] in the text.
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
        out[currentState] |= (1 << i); // There's a match of keywords[i] at node currentState.
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
                out[g[state][c]] |= out[failure]; // Merge out values
                q.push(g[state][c]);
            }
        }
    }

    return states;
}


// Print out the 3 arrays necessary to a file.
void outputArrays() {
    std::ofstream savefile("arrays.h");
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

    savefile << "int f[" << MAXS << "] = {\n\t";
    for (int i = 0; i < MAXS-1; i++) {
        savefile << f[i] << ", ";
    }
    savefile << f[MAXS-1] << "\n};\n\n";

    savefile << "int out[" << MAXS << "] = {\n\t";
    for (int i = 0; i < MAXS-1; i++) {
        savefile << out[i] << ", ";
    }
    savefile << out[MAXS-1] << "\n};\n\n";

    savefile << "const int terms = " << numTerms << ";\n\n";
    savefile.close();
}

// Build the AC matching machine from the given words
// TODO: Make this a 2D array-based system
void ACbuild() {
    vector<string> keywords;
    keywords.push_back("he");
    keywords.push_back("she");
    keywords.push_back("hers");
    keywords.push_back("his");
    keywords.push_back("asdk");
    numTerms = keywords.size();
    buildMatchingMachine(keywords);
    outputArrays();
}

int main(){
	ACbuild();
	return 0;
}

