#ifndef POOL1_LAYER_H
#define POOL1_LAYER_H

#define CHANNELS_P1    32     
#define IN_HW_P1   28    
#define WIN     2      
#define STRIDE  2
#define OUT_HW_P1  (IN_HW_P1 / STRIDE)   

void pool1(const float A[CHANNELS_P1][IN_HW_P1][IN_HW_P1], float B[CHANNELS_P1][OUT_HW_P1][OUT_HW_P1]);

#endif 
