#include <stdio.h>
#include <string.h>
#include <iostream>
#include "BM.h"
#include "terms.h"
#include "arrays.h"
#define ASIZE 256

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))


using namespace std;

int BMsearch(char y[INPUTSIZE]) {
   
	int m = MATCHSIZE-1;
	int n = INPUTSIZE-1;
 
   /* Searching */
   j = 0;
   while (j <= n - m) {
      for (i = m - 1; i >= 0 && x[i] == y[i + j]; --i);
      if (i < 0) {
         printf("%d\n", j);
         return j;
         j += bmGs[0];
      }
      else
         j += MAX(bmGs[i], bmBc[y[i + j]] - m + 1 + i);
   }
	 return -1;
}

void dut(
	hls::stream<char> &strm_in,
	hls::stream<int> &strm_out		
) {	
   char y[INPUTSIZE];
	static int i=0;
	int match_found=-1;
	int j;
	y[i++] = strm_in.read();
	if (i < 255) {
		match_found = -1;
	} else {
	  cout << "running BM..." << endl;
		match_found = BMsearch(y);
		i=0;
	}
  strm_out.write( match_found );
}




