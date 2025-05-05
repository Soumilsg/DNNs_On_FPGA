// first‑layer convolution  (32x32x3 - 28x28x32)
#include <ap_int.h>
#include <hls_math.h>

#include "conv2d_layer1.h"

/////////////////PRAGMAS/////////////////



//////////////////////////////////

void conv1(float X[IN_CH][IN_HW][IN_HW], float Y[OUT_CH][OUT_HW][OUT_HW]) {
	// Saw online valuable for system-lvel wrapping
	#pragma HLS INTERFACE mode=ap_memory port=X depth=IN_CH*IN_HW*IN_HW
	#pragma HLS INTERFACE mode=ap_memory port=Y depth=OUT_CH*OUT_HW*OUT_HW
	// Set the weights to be stored on the fast block RAM
	#pragma HLS bind_storage variable=CONV1_W type=RAM_1P impl=bram
	#pragma HLS bind_storage variable=CONV1_B type=ROM_1P impl=bram


	// Got the Partitioning from Lecture (Weights are 32x3x5x5, splitting across channels and convolutional kernel)
	#pragma HLS ARRAY_PARTITION variable=CONV1_W dim=2 complete
	#pragma HLS ARRAY_PARTITION variable=CONV1_W dim=3 complete
	#pragma HLS ARRAY_PARTITION variable=CONV1_W dim=4 complete
	#pragma HLS ARRAY_PARTITION variable=X       dim=1 complete
	#pragma HLS PIPELINE II=1
	M_: for (int m = 0; m < OUT_CH; m++) { 	// For every output channel
		Y_: for (int y = 0; y < OUT_HW; y++) {	// For every output row
			X_ : for (int x = 0; x < OUT_HW; x++) {	// For every output column
				#pragma HLS PIPELINE II=1
				float acc = CONV1_B[m];
				C_ : for (int c = 0; c < IN_CH; c++) {	// For every input channel
					KY_ : for (int ky = 0; ky < K; ky++) {	// For every kernel row
						KX_ : for (int kx = 0; kx < K; kx++) {	// For every kernel col.
							acc += X[c][y+ky][x+kx] * CONV1_W[m][c][ky][kx];
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
