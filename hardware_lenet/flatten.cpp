// 5*5*32 = 800
#include "flatten.h"

#pragma HLS INTERFACE mode=ap_memory port=in  depth=CH_FL*HW_FL*HW_FL
#pragma HLS INTERFACE mode=ap_memory port=out depth=IN_SIZE_FL
#pragma HLS ARRAY_PARTITION variable=in dim=1 complete

void flatten(const float X[CH_FL][HW_FL][HW_FL], float Y[IN_SIZE_FL]) {
    #pragma HLS PIPELINE II=1

    int idx = 0;                      
    for (int c = 0; c < CH_FL; c++){  
        for (int y = 0; y < HW_FL; y++){
            for (int x = 0; x < HW_FL; x++){
                Y[idx] = X[c][y][x];
                idx = idx + 1;
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

