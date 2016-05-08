//===========================================================================
// digitrec.h
//===========================================================================
// @brief: This header file defines the interface for the core functions.

#ifndef AC_H
#define AC_H

#include<hls_stream.h>

void dut(
    hls::stream<char> &strm_in,
	hls::stream<int>  &strm_out
);



#endif
