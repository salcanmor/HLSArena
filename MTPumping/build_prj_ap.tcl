#################
#    HLS4ML
#################
open_project -reset myproject_prj_ap
set_top mult_accum
add_files example_ap.cc -cflags "-std=c++0x -I[file normalize ../../nnet_utils]" 
add_files -tb testbench_ap.cc -cflags "-std=c++0x -I[file normalize ../../nnet_utils]"
#add_files -tb tb_data
open_solution -reset "solution1"
set_part {xcku115-flvf1924-2-i}
create_clock -period 1 -name default
csim_design
csynth_design
cosim_design -trace_level all
#export_design -format ip_catalog
