#=============================================================================
# run-float.tcl 
#=============================================================================
# @brief: A Tcl script for floating-point experiments.
#
# @desc: This script runs a batch of simulation & synthesis experiments
# to explore trade-offs between accuracy, performance, and area for 
# floating-point implementation of the CORDIC core.
#
# 1. The user specifies number_itertions
# 2. Results are collected in a single file ./result/float-result.csv
# 3. out.dat from each individual experiment is also copied to ./result 

#------------------------------------------------------
# You can specify a set of iteration counts to explore.
#------------------------------------------------------
#set num_iterations { 4 6 8 10 12 14 16 18 20 22 }

#------------------------------------------------------
# run batch experiments
#------------------------------------------------------
# Open/reset the project
open_project hls_prj
# Top function of the design is "cordic"
set_top BM

# Add design and testbench files
add_files BM.c -cflags "-DBIT_ACCURATE" 

open_solution "solution1"
# Use Zynq device
set_part {xc7z020clg484-1}

# Target clock period is 10ns
create_clock -period 10

# Synthesis the design
csynth_design

#cosim_design

#---------------------------------------------
# Collect & dump out results from HLS reports
#---------------------------------------------
#set filename "BM_result.csv"
#set argv [list $filename $hls_prj]
#set argc 2
#source "./script/collect_result.tcl"

