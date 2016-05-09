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
	  // Timer
  Timer vtimer("aho-corasick verification");
	Timer ttimer("aho-corasick tests");
  vtimer.start();
  
	cout << "Verifying known matches..." << endl;
	ifstream file("../../snort/verifStrings.txt");
	string str;
	cout << "Expect Recognition for these tests..." << endl;
	while(getline(file, str)) {
		callSearch(str, str.length());
	}

	cout << "Expect recognition for these hex tests..." << endl;
	ifstream hexFile("../../snort/verifStringsHex.txt");
	while(getline(hexFile, str)) {
		string conv = hex_to_string(str);
		callSearch(conv, conv.length());
	}	
	vtimer.stop();
	
	ttimer.start();
	
	cout << "Begin full 64kB test..." << endl;
	ifstream testFile("../../snort/testMatchPacket1.txt");
	while(getline(testFile, str)) {
		callSearch(str, str.length());
	}

	ifstream testFile2("../../snort/testMatchPacket2.txt");
	while(getline(testFile2, str)) {
		callSearch(str, str.length());
	}

	ifstream testFile3("../../snort/testCleanPacket.txt");
	while(getline(testFile2, str)) {
		callSearch(str, str.length());
	}
	
	ttimer.stop();


  return 0;
}


