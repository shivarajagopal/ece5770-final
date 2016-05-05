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
    while (g[answer][c] == -1) answer = f[answer];
    return g[answer][c];
}

int ACsearch( char character, char reset ) { //char text[13], int textLength ) {
    static int currentState = 0;
		if (reset) currentState = 0;
		int firstMatch = -1;
		char matched = 0;
		currentState = findNextState(currentState, character);
		if (out[currentState] == 0) return firstMatch;
		for (int j = 0; j < terms; ++j) {
			if (out[currentState] & (1 << j)) { // Matched keywords[j]
				if (!matched) {
					firstMatch= j;
					matched = 1;
				}
      }
		}
		return firstMatch;
}

