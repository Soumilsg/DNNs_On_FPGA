#ifndef CONV1_PARAMS_H
#define CONV1_PARAMS_H

#define IN_CH     3
#define OUT_CH   32
#define K        5
#define IN_HW   32
#define OUT_HW  28

static const float CONV1_W[OUT_CH][IN_CH][K][K] = { … };
static const float CONV1_B[OUT_CH]              = { … };

extern void conv1(float X[IN_CH][IN_HW][IN_HW], float Y[OUT_CH][OUT_HW][OUT_HW]);

#endif