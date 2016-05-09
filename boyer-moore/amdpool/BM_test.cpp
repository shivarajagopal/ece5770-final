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
#include "BM.h"
#include "timer.h"
using namespace std;
//------------------------------------------------------------------------
// Boyer-Moore testbench
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
		ac_in.write(array[i]);
		dut ( ac_in, ac_out );
		matched = ac_out.read();
	}
	if (matched != -1) {
		cout << "Matched at Location "<< matched << endl;
	}
	else {
		cout << "No matches found!!" << endl;
	}

}


int main(int argc, char *argv[]) 
{
  int matched, i;
	
string str4 = "iywefbevhliweybfvioweyblvyewvfileyvseorigybeioybgwebtyweuietyshellcodeyvweoyvawlo=asweiawebiotywe;obtysweovbtyebtyawlytaw348lobtyebysweybwerioy bweoty bweoivbtyeiovbtyweiobyweivbtyawleybt aweiuvtybweiotyvbaweioyvbtweiortyvbwevbweybttyweyvbtwtyvbwybytytigit";
  // Timer
  Timer timer("boyer-moore");
  timer.start();
	
	
	callSearch(str4, str4.length());
	/*
	callSearch(str2, 13);
	callSearch(str3, 13);
	callSearch(str4, 15);
	callSearch(str5, 36);
	callSearch(str6, 13);
  */
	
	timer.stop();

  return 0;
}


