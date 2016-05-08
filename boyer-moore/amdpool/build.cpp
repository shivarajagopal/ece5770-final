#include <stdio.h>
#include <string.h>
#include <iostream>
#include "BM.h"
#include "terms.h"
#define ASIZE 256

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

using namespace std;

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

// Print out the 3 arrays necessary to a file.
void outputArrays(int bmGs[], int size1, int bmBc[], int size2) {
	// Open file
	std::ofstream savefile("arrays.h");

	// Output bmGs
	savefile << "int bmGs[" << size1 << "] = {\n\t";
    for (int i = 0; i < size1-1; i++) {
        savefile << bmGs[i] << ", ";
    }
    savefile << bmGs[size1-1] << "\n};\n\n";

    // Output bmBc
	savefile << "int bmBc[" << size2 << "] = {\n\t";
    for (int i = 0; i < size2-1; i++) {
        savefile << bmBc[i] << ", ";
    }
    savefile << bmBc[size2-1] << "\n};\n\n";

	// Close file
    savefile.close();

}

void build(char x[MATCHSIZE], char y[INPUTSIZE]) {
   
	int m = MATCHSIZE-1;
	int n = INPUTSIZE-1;

	int i, j, bmGs[m], bmBc[ASIZE];
 
   	/* Preprocessing */
   	preBmGs(x, m, bmGs);
   	preBmBc(x, m, bmBc);

   	outputArrays(bmGs, m, bmBc, ASIZE);
}

int main() {
	build(x, y);
}




