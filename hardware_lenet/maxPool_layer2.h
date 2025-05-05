#ifndef POOL2_LAYER_H
#define POOL2_LAYER_H

#define CHANNELS_P2    32     
#define IN_HW_P2    10    
#define WIN         2      
#define STRIDE      2
#define OUT_HW_P2   (IN_HW_P2 / STRIDE)   

void pool2(const float A[CHANNELS_P2][IN_HW_P2][IN_HW_P2], float B[CHANNELS_P2][OUT_HW_P2][OUT_HW_P2]);

#endif 
