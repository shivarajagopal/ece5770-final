#include <stdio.h>
#include <string.h>
#include <iostream>
#include "BM.h"
#include "terms.h"
#include "arrays.h"
#define ASIZE 256

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))


using namespace std;

char y[INPUTSIZE];
int BMsearch(char y[INPUTSIZE]) {
	 int i, j, k, l;   
	 int m = MATCHSIZE-1;
	 int n = INPUTSIZE-1;
	 int matched, matchedj;
   /* Searching */
   j = 0;
	 int iter = 0;
	 matchedj = -1;
	 matched = 0;
   for (iter=0; iter < n-m; iter++) {
	   if (j <= n-m && (!matched)) {
				i = m-1;
				for (l = 0 ; l < m ; l++) {
					if ((x[i] == y[i+j]) && (i >= 0)) {
						i--;
					}
				}
				if (i < 0) {
					matched = 1;
					matchedj = j;
					j += bmGs[0];
				}
				else {
					j += MAX(bmGs[i], bmBc[y[i + j]] - m + 1 + i);
				}
		 }
   }
	 return matchedj;
}

void dut(
	hls::stream<char> &strm_in,
	hls::stream<int> &strm_out		
) {	
	static int i=0;
	int match_found=-1;
	int j;
	char inputChar = strm_in.read();
	y[i++] = inputChar;
	if (i < 256) {
		match_found = -1;
	} else {
		//cout << "running BM..." << endl;
		match_found = BMsearch(y);
		i=0;
	}
  strm_out.write( match_found );
}




