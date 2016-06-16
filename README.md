# ece5770-final
A project to compare HLS-synthesized versions of string matching algorithms

## Overview
The project contains C++ implementations of the Boyer-Moore single-string matching algorithm and the Aho-Corasick multi-string matching algorithm. The code is written for synthesis using Xilinx Vivado HLS, and contains many HLS-based optimizations, including static memory allocation.

The two algorithms are divided into two separate steps that can be compiled by the Makefile. The build step creates the state machines and supporting data for the string matching based on the definitions, since these can be determined offline from the FPGA. The search step then uses a generated header file with the built rules to search an input text string. 

The Snort rules we used for this project are based on the shellcode rules included in the Snort community rules. The rules themselves are divided into hexadecimal rules and ASCII rules so that they can be processed by our code separately. The rules are of varying length, and are tailored to mostly fill the block RAM of the Xilinx Zedboard.
