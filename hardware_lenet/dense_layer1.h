#ifndef DENSE1_LAYER_H
#define DENSE1_LAYER_H

#define IN_D1   800
#define OUT_D1   64

static const float D1_W[OUT_D1][IN_D1] = {};
static const float D1_B[OUT_D1] = {};

void dense1(const float X[IN_D1], float Y[OUT_D1]);

#endif
