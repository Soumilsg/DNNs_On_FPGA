// Look at 2x2 windows and output the maximum of the four numbers, making the input 28x28 become output 14x14
#include <ap_int.h>
#include <hls_math.h>

#include "dense_layer1.h"

/////////////////PRAGMAS/////////////////

// Saw online valuable for system-level wrapping
#pragma HLS INTERFACE mode=ap_memory port=X depth=IN_D1
#pragma HLS INTERFACE mode=ap_memory port=Y depth=OUT_D1

// Set the weights to be stored on the fast block RAM
#pragma HLS RESOURCE variable=D1_W core=RAM_1P_BRAM
#pragma HLS RESOURCE variable=D1_B core=RAM_1P_BRAM

#pragma HLS ARRAY_PARTITION variable=D1_W dim=2 complete
//////////////////////////////////

void dense1(const float X[IN_D1], float Y[OUT_D1]) {
    #pragma HLS PIPELINE II=1

    O_: for (int o = 0; o < OUT_D1; o++) {
    float acc = D1_B[o];
        I_:  for (int i = 0; i < IN_D1; i++) {
            acc += X[i] * D1_W[o][i];
        }
        if (acc < 0.0f) {
            Y[o] = 0.0f;
        } else {
            Y[o] = acc;
        }
    }
}

// model = Sequential([
//     keras.Input(shape=(32, 32, 3)),
//     layers.Conv2D(filters=32, kernel_size=(5, 5), strides=(1, 1), padding='valid', activation='relu', name="CONV1"),
//     layers.MaxPooling2D(pool_size=(2, 2), strides=(2, 2), name="POOLING1"),
//     layers.Conv2D(filters=32, kernel_size=(5, 5), strides=(1, 1), padding='valid', activation='relu', name="CONV2"),
//     layers.MaxPooling2D(pool_size=(2, 2), strides=(2, 2), name="POOLING2"),
//     layers.Flatten(),
//     layers.Dense(64, activation='relu', name="FULLY1"),
//     layers.Dense(43, activation='softmax', name="FULLY2"),
// ])

