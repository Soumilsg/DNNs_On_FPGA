// Look at 2x2 windows and output the maximum of the four numbers, making the input 28x28 become output 14x14
#include <ap_int.h>
#include <hls_math.h>

#include "maxPool_layer1.h"

/////////////////PRAGMAS/////////////////


//////////////////////////////////

void pool1(const float A[CHANNELS_P1][IN_HW_P1][IN_HW_P1], float B[CHANNELS_P1][OUT_HW_P1][OUT_HW_P1]) {

	#pragma HLS ARRAY_PARTITION variable=A dim=1 complete
	#pragma HLS ARRAY_PARTITION variable=B dim=1 complete
	// Saw online valuable for system-lvel wrapping
    #pragma HLS INTERFACE mode=ap_memory port=A depth=CHANNELS_P1*IN_HW_P1*IN_HW_P1
    #pragma HLS INTERFACE mode=ap_memory port=B depth=CHANNELS_P1*OUT_HW_P1*OUT_HW_P1
    #pragma HLS PIPELINE II=1
    
    CH_:  for (int m = 0; m < CHANNELS_P1;   m++) { // For every output channel
        Y_:   for (int y = 0; y < OUT_HW_P1; y++) {  // For every output row
            X_:   for (int x = 0; x < OUT_HW_P1; x++) { // For every output col

            int in_y = y * STRIDE; 
            int in_x = x * STRIDE;

            float max01, max23, result;
            float a0 = A[m][in_y][in_x];
            float a1 = A[m][in_y][in_x + 1];
            if (a0 > a1) {
                max01 = a0;
            } else {
                max01 = a1;
            }
            float a2 = A[m][in_y + 1][in_x];
            float a3 = A[m][in_y + 1][in_x + 1];
            if (a2 > a3) {
                max23 = a2;
            } else {
                max23 = a3;
            }
            if (max01 > max23) {
                result = max01;
            } else {
                result = max23;
            }

            B[m][y][x] = result;
            }
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

