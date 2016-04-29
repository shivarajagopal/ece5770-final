//=========================================================================
// testbench.cpp
//=========================================================================
// @brief: testbench for k-nearest-neighbor digit recongnition application

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

#include "ac.h"
#include "timer.h"

//------------------------------------------------------------------------
// Aho-Corasick testbench
//------------------------------------------------------------------------

int main(int argc, char *argv[]) 
{
  int matched, i;

	char str1[13] = "asdkweoijloh";
	char str2[13] = "hesdlfjasklj";
	char str3[13] = "sheksladjfkl";
	char str4[13] = "dfdsherssdfs";
	char str5[13] = "sdlafjlkshis";

  // Timer
  Timer timer("aho-corasick");
  
  timer.start();
  
	int result1 =  ACsearch(str1, 13);
	std::cout << "Expected: 4\tActual: "<< result1 << std::endl;
  int result2 =  ACsearch(str2, 13);
	std::cout << "Expected: 0\tActual: "<< result2 << std::endl;
  int result3 =  ACsearch(str3, 13);
	std::cout << "Expected: 1\tActual: "<< result3 << std::endl;
  int result4 =  ACsearch(str4, 13);
	std::cout << "Expected: 2\tActual: "<< result4 << std::endl;
  int result5 =  ACsearch(str5, 13);
	std::cout << "Expected: 3\tActual: "<< result5 << std::endl;
 
  timer.stop();

  //classification = classifySound(nn, result);
  //std::cout << "classification: " << classification << "\n";
  return 0;
}


