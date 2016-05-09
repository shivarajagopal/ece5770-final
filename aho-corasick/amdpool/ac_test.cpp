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

void callSearch (const string& array, int length) {
	int i;
	int matched = -1;
	for (i = 0; i < length; i++) {
		if (i == 0) {
			ac_in.write(array[i]);
			ac_in.write( 0x01 );
		} else { 
			ac_in.write(array[i]);
			ac_in.write( 0x00 );
		}
		dut ( ac_in, ac_out );
		matched = ac_out.read();
		if (matched != -1) {
			std::cout << "Recognized String "<< matched << std::endl;
			matched = 1;
			break;
		}
	}
	if (matched != 1) 	std::cout << "No matches found!!" << std::endl;

}


int main(int argc, char *argv[]) 
{
  int matched, i;
	string str1 = "asdkweoijloh";
	string str2 = "hesdlfjasklj";
	string str3 = "sheksladjfkl";
	string str4 = "asefjshellcode";
	string str5 = "RERERERERERERERERERERERERERERERERas";
	string str6 = hex_to_string("6B3C240B60030C246A658712");
	ifstream file("../../snort/testStrings.txt");
	string str;
	while(getline(file, str)) {
		cout << str << endl;
	}
	ifstream hexFile("../../snort/testStringsHex.txt");
	while(getline(hexFile, str)) {
		cout << hex_to_string(str)) << endl;
	}
  // Timer
  Timer timer("aho-corasick");
  timer.start();
	
	
	callSearch(str1, str1.length());
	callSearch(str2, str2.length());
	callSearch(str3, str3.length());
	callSearch(str4, str4.length());
	callSearch(str5, str5.length());
	callSearch(str6, str6.length());
  
	
	timer.stop();

  return 0;
}


