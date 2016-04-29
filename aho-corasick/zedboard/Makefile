#==========================================================================
# Makefile
#==========================================================================
# @brief: A makefile the compiles and runs the digitrec program
#
# @desc: 1. "make" or "make sw" runs software execution by default
#        2. "make fpga" invokes the HW accelerator
#        3. "make clean" cleans up the directory


INC_PATH=/usr/include/vivado_hls/2015.2
CFLAGS = -I${INC_PATH}

all: sw

sw: digitrec.cpp digitrec_test.cpp
	@echo "Compiling & executing digitrec software program on ARM ..."
	g++ ${CFLAGS} digitrec.cpp digitrec_test.cpp -o digitrec-arm
	./digitrec-arm

fpga: host.cpp
	@echo "Compiling host program & running digitrec accelerator ..."
	g++ ${CFLAGS} host.cpp -o digitrec-fpga
	./digitrec-fpga

# Clean up the directory before submission
clean:
	@echo "Clean up output files"
	rm -rf digitrec-sw vivado_hls.log *.prj result out.dat *~
	rm -rf digitrec-fpga
