#ifndef DENSE2_LAYER_H
#define DENSE2_LAYER_H

#define IN_D2   64
#define OUT_D2  43

static const float D2_W[OUT_D2][IN_D2] = {};
static const float D2_B[OUT_D2] = {};

void dense2(const float X[IN_D2], float Y[OUT_D2]);

#endif
