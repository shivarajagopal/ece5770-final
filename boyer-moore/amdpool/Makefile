#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and runs the cordic program
#
# @desc: 1. "make float" compiles & executes the floating-point implementation
#        2. "make fixed" compiles & executes the fixed-point implementation
#        3. "make clean" cleans up the directory

# Extract Vivado HLS include path
VHLS_PATH := $(dir $(shell which vivado_hls))/..
VHLS_INC ?= ${VHLS_PATH}/include

# default runs floating-point implementation
all: BM.c
	g++ -I$(VHLS_INC) BM.c -o BM 
	./BM

# Clean up the directory before submission
clean:
	@echo "Clean up output files"
	rm -rf result *.prj *.log *.dat BM 
