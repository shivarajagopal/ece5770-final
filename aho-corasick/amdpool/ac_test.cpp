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
//#include "testStrings.h" 
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

inline int callSearch (const string& array, int length) {
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
			return matched;
		}
	}
	if (matched != 1) return -1;

}


int main(int argc, char *argv[]) 
{
  int matched, i;
	  // Timer
  Timer vtimer("aho-corasick verification");
	Timer ttimer("aho-corasick tests");
	string str;
	int retValue;
  vtimer.start();
  
	cout << "Verifying known matches..." << endl;
	ifstream file("../../snort/verifStrings.txt");
	cout << "Expect Recognition for these tests..." << endl << endl;
	while(getline(file, str)) {
		callSearch(str, str.length());
	}
	cout << endl;
	cout << "Expect recognition for these hex tests..." << endl << endl;
	ifstream hexFile("../../snort/verifStringsHex.txt");
	while(getline(hexFile, str)) {
		string conv = hex_to_string(str);
		callSearch(conv, conv.length());
	}	
	vtimer.stop();
	
	ttimer.start();
	cout << endl;
	cout << "Begin full 64kB test..." << endl << endl;
	int counter;
	string tempStr;
	
	ifstream testFile1("testMatchPacket1.txt");
	counter=0; str = ""; matched = 0;

	for (int k = 0; k < 256; k++) {	
		for (int l = 0; l < 16; l++) {
			getline(testFile1, tempStr);
			str += tempStr;
			counter++;
		}
		retValue = callSearch(str, str.length());
		if (retValue != -1) {
			matched= 1;
		}
		counter = 0;
		str = "";
	}
	if (!matched) cout << "No match found for this packet" <<endl;

	ifstream testFile2("testMatchPacket2.txt");
	counter=0; str = ""; matched = 0;

	for (int k = 0; k < 256; k++) {	
		for (int l = 0; l < 16; l++) {
			getline(testFile2, tempStr);
			str += tempStr;
			counter++;
		}
		retValue = callSearch(str, str.length());
		if (retValue != -1) {
			matched= 1;
		}
		counter = 0;
		str = "";
	}
	if (!matched) cout << "No match found for this packet" <<endl;

	ifstream testFile3("testCleanPacket.txt");
	counter=0; str = ""; matched = 0;

	for (int k = 0; k < 256; k++) {	
		for (int l = 0; l < 16; l++) {
			getline(testFile3, tempStr);
			str += tempStr;
			counter++;
		}
		retValue = callSearch(str, str.length());
		if (retValue != -1) {
			matched= 1;
		}
		counter = 0;
		str = "";
	}
	if (!matched) cout << "No match found for this packet" <<endl;

	cout << endl;

	ttimer.stop();


  return 0;
}


