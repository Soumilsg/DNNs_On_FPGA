#ifndef CONV2_PARAMS_H
#define CONV2_PARAMS_H

#define IN_CH_C2     32
#define OUT_CH_C2    32
#define K_C2         5
#define IN_HW_C2     14
#define OUT_HW_C2    (IN_HW_C2-K_C2+1)

static const float CONV2_W[OUT_CH_C2][IN_CH_C2][K_C2][K_C2] = { … };
static const float CONV2_B[OUT_CH_C2]              = { … };

extern void conv2(float X[IN_CH_C2][IN_HW_C2][IN_HW_C2], float Y[OUT_CH_C2][OUT_HW_C2][OUT_HW_C2]);

#endif