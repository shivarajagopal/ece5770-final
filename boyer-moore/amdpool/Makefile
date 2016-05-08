#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and synthesizes the digitrec program
#
# @desc: 1. "make" runs csim by default
#        2. "make csim" compiles & executes the fixed-point implementation
#        3. "make clean" cleans up the directory


# Extract Vivado HLS include path
VHLS_PATH := $(dir $(shell which vivado_hls))/..
VHLS_INC ?= ${VHLS_PATH}/include

CFLAGS = -g -I${VHLS_INC} 

all: csim

csim: clean search
	@echo "Simulating searcher on amdpool"
	./search

bitstream: 
	@echo "Synthesizing digitrec and creating bitstream on amdpool ..."
	vivado_hls -f run_pipeline.tcl
	./run_bitstream.sh

clean:
	rm -rf search *.dat *.prj *.log
	rm -rf zedboard_project/ xillydemo.bit

search: BM.cpp BM_test.cpp
	@echo "Compiling searcher..."
	g++ ${CFLAGS} $^ -o search

HLS: csim
	@echo "Compiling and simulating using Vivado HLS"
	vivado_hls run.tcl

old: BM.cpp
	@echo "Compiling old version"
	g++ ${CFLAGS} $^ -o old
	./old
