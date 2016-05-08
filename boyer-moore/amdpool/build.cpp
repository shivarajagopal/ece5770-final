#include <stdio.h>
#include <string.h>
#include <iostream>
#include "BM.h"
#define ASIZE 256

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

#define MATCHSIZE 10
#define INPUTSIZE 256
using namespace std;


char x[MATCHSIZE] = "shellcode";
char y[INPUTSIZE]= "aweihswshellcodebuilhvbseby76348oyweuyvl38ty w38yt 2938yv5239tw3rta37v awlrtavl237ifvwuig37lt523rywityr q.wylawearty;w3rtyW>Orqwo8ry qlwr8tyfweihtvblwi4ytw38lvty3ty238lvta3ilwvfgaw348lwvawileuvg aw3iltr23lvtgaw3ilvtfawilvftw3kftyweuivtyweift28lv8issdfe829";

void preBmBc(char *x, int m, int bmBc[]) {
   int i;
 
   for (i = 0; i < ASIZE; ++i)
      bmBc[i] = m;
   for (i = 0; i < m - 1; ++i)
      bmBc[x[i]] = m - i - 1;
}
 
void suffixes(char *x, int m, int *suff) {
   int f, g, i;
 
   suff[m - 1] = m;
   g = m - 1;
   for (i = m - 2; i >= 0; --i) {
      if (i > g && suff[i + m - 1 - f] < i - g)
         suff[i] = suff[i + m - 1 - f];
      else {
         if (i < g)
            g = i;
         f = i;
         while (g >= 0 && x[g] == x[g + m - 1 - f])
            --g;
         suff[i] = f - g;
      }
   }
}
 
void preBmGs(char *x, int m, int bmGs[]) {
   int i, j, suff[m];
 
   suffixes(x, m, suff);
 
   for (i = 0; i < m; ++i)
      bmGs[i] = m;
   j = 0;
   for (i = m - 1; i >= 0; --i)
      if (suff[i] == i + 1)
         for (; j < m - 1 - i; ++j)
            if (bmGs[j] == m)
               bmGs[j] = m - 1 - i;
   for (i = 0; i <= m - 2; ++i)
      bmGs[m - 1 - suff[i]] = m - 1 - i;
}

int BM(char x[MATCHSIZE], char y[INPUTSIZE]) {
   
	 int m = MATCHSIZE-1;
	 int n = INPUTSIZE-1;

	 int i, j, bmGs[m], bmBc[ASIZE];
 
   /* Preprocessing */
   preBmGs(x, m, bmGs);
   preBmBc(x, m, bmBc);
 
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
	static int i=0;
	int match_found=-1;
	int j;
	y[i++] = strm_in.read();
	if (i < 255) {
		match_found = -1;
	} else {
	  cout << "running BM..." << endl;
		match_found = BM(x, y);
		i=0;
	}
  strm_out.write( match_found );
}




