############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project CustomDNN
set_top cnn_top
add_files maxPool_layer2.h
add_files maxPool_layer2.cpp
add_files maxPool_layer1.h
add_files maxPool_layer1.cpp
add_files flatten.h
add_files flatten.cpp
add_files dense_layer2.h
add_files dense_layer2.cpp
add_files dense_layer1.h
add_files dense_layer1.cpp
add_files conv2d_layer2.h
add_files conv2d_layer2.cpp
add_files conv2d_layer1.h
add_files conv2d_layer1.cpp
add_files cnn_top.h
add_files cnn_top.cpp
add_files -tb testbench.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020iclg400-1L}
create_clock -period 10 -name default
config_export -vivado_clock 10
#source "./CustomDNN/solution1/directives.tcl"
csynth_design
