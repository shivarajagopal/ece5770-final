//=========================================================================
// testbench.cpp
//=========================================================================
// @brief: testbench for k-nearest-neighbor digit recongnition application

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "ac.h"
#include "timer.h"
using namespace std;
//------------------------------------------------------------------------
// Aho-Corasick testbench
//------------------------------------------------------------------------
hls::stream<char> ac_in;
hls::stream<int>  ac_out;

std::string hex_to_string(const std::string& input)
{
	static const char* const lut = "0123456789ABCDEF";
	size_t len = input.length();
	if (len & 1) throw std::invalid_argument("odd length");
	
	std::string output;
	output.reserve(len / 2);
	for (size_t i = 0; i < len; i += 2)
	{
		char a = input[i];
		const char* p = std::lower_bound(lut, lut + 16, a);
		if (*p != a) throw std::invalid_argument("not a hex digit");
		
		char b = input[i + 1];
		const char* q = std::lower_bound(lut, lut + 16, b);
		if (*q != b) throw std::invalid_argument("not a hex digit");
		
		output.push_back(((p - lut) << 4) | (q - lut));
	}
	return output;
}

void callSearch (char* array, int length) {
	int i;
	int matched = -1;
	for (i = 0; i < length; i++) {
		if (i == 0) {
			ac_in.write(array[i]);
			ac_in.write((char) 1 );
		} else { 
			ac_in.write(array[i]);
			ac_in.write((char) 0 );
		}
		dut ( ac_in, ac_out );
		matched = ac_out.read();
		if (matched != -1) {
			std::cout << "Recognized String "<< matched << std::endl;
			break;
		}
	}
}


int main(int argc, char *argv[]) 
{
  int matched, i;
	
	char str1[13] = "asdkweoijloh";
	char str2[13] = "hesdlfjasklj";
	char str3[13] = "sheksladjfkl";
	char str4[13] = "dfdsherssdfs";
	char str5[13] = "sdlafjlkshis";
	char str6[13] = {0x6B, 0x3C, 0x24, 0x0B, 0x60, 0x03, 0x0C, 0x24, 0x6A, 0x65, 0x87, 0x12, '\0'};
  // Timer
  Timer timer("aho-corasick");
  timer.start();
	
	
	callSearch(str1, 13);
	callSearch(str2, 13);
	callSearch(str3, 13);
	callSearch(str4, 13);
	callSearch(str5, 13);
	callSearch(str6, 13);
  
	
	timer.stop();

  return 0;
}


