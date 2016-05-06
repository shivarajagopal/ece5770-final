#include <iostream>

#include "arrays.h"
#include "ac.h"
using namespace std;
// Finds the next state the machine will transition to.
//
// currentState - The current state of the machine. Must be between
//                0 and the number of states - 1, inclusive.
// nextInput - The next character that enters into the machine. Should be between lowestChar 
//             and highestChar, inclusive.
// lowestChar - Should be the same lowestChar that was passed to "buildMatchingMachine".

// Returns the next state the machine will transition to. This is an integer between
// 0 and the number of states - 1, inclusive.
int findNextState(int currentState, char nextInput) {
    int answer = currentState;
    int c = nextInput;
		int i;
	 	for (i=0; i < 5; ++i) {
			if (g[answer][c] == -1)
				answer = f[answer];
		}
		/*while (g[answer][c] == -1){
		 	answer = f[answer];
		}
		cout << "max: " << max << endl;*/
    return g[answer][c];
}

int ACsearch( char character, char reset ) { //char text[13], int textLength ) {
		static int currentState = 0;
		if (reset) currentState = 0;
		int firstMatch = -1;
		char matched = 0;
		currentState = findNextState(currentState, character);
		//cout << "curState: " << currentState << endl;
		
		//if (out[currentState] == 0) return firstMatch;
		//cout << "out["<<currentState<<"] = " << out[currentState] <<endl;
		for (int j = 0; j < terms; ++j) {
			if (out[currentState][j]) { // Matched keywords[j]
				if (!matched) {
					firstMatch= j;
					matched = 1;
				}
      }
		}
		return firstMatch;
}

void dut(
		hls::stream<char> &strm_in,
		hls::stream<char> &reset_in,
		hls::stream<int> &strm_out
)
{
	char in_char;
	char reset;
	int  match_found;
	
	in_char = strm_in.read();
	reset = reset_in.read();
	//cout << "char: " << in_char << " reset: " << (int)reset << endl;

	match_found = ACsearch(in_char, reset);
	//cout << "Match found: " << match_found << endl;	
	strm_out.write( match_found );
}
