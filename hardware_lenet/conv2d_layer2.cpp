// second‑layer convolution  (14x14x32 - 10x10x32)
#include <ap_int.h>
#include <hls_math.h>

#include "conv2d_layer2.h"

/////////////////PRAGMAS/////////////////


// Set the weights to be stored on the fast block RAM

//////////////////////////////////

void conv2(float X[IN_CH_C2][IN_HW_C2][IN_HW_C2], float Y[OUT_CH_C2][OUT_HW_C2][OUT_HW_C2]) {
	// Saw online valuable for system-lvel wrapping
	#pragma HLS bind_storage variable=CONV2_W type=RAM_1P impl=bram
	#pragma HLS bind_storage variable=CONV2_B type=ROM_1P impl=bram

	// Got the Partitioning from Lecture (Weights are 32x3x5x5, splitting across channels and convolutional kernel)
	#pragma HLS ARRAY_PARTITION variable=CONV2_W dim=2 complete
	#pragma HLS ARRAY_PARTITION variable=CONV2_W dim=3 complete
	#pragma HLS ARRAY_PARTITION variable=CONV2_W dim=4 complete
	#pragma HLS ARRAY_PARTITION variable=X       dim=1 complete
	#pragma HLS INTERFACE mode=ap_memory port=X depth=IN_CH_C2*IN_HW_C2*IN_HW_C2
	#pragma HLS INTERFACE mode=ap_memory port=Y depth=OUT_CH_C2*OUT_HW_C2*OUT_HW_C2

	#pragma HLS PIPELINE II=1
	M_: for (int m = 0; m < OUT_CH_C2; m++) { 	// For every output channel
		Y_: for (int y = 0; y < OUT_HW_C2; y++) {	// For every output row
			X_ : for (int x = 0; x < OUT_HW_C2; x++) {	// For every output column
				float acc = CONV2_B[m];
				C_ : for (int c = 0; c < IN_CH_C2; c++) {	// For every input channel
					KY_ : for (int ky = 0; ky < K_C2; ky++) {	// For every kernel row
						KX_ : for (int kx = 0; kx < K_C2; kx++) {	// For every kernel col.
							acc += X[c][y+ky][x+kx] * CONV2_W[m][c][ky][kx];
						}
					}
				}
				// Apply RELU Activation Function
				if (acc < 0.0f) {
					Y[m][y][x] = 0.0f;
				}
				else {
					Y[m][y][x] = acc;
				}
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
