// Chain all layers together
#include "conv2d_layer1.h"      // IN_CH, IN_HW, OUT_CH, OUT_HW
#include "maxPool_layer1.h"     // CHANNELS_P1, OUT_HW_P1
#include "conv2d_layer2.h"      // OUT_CH_C2, OUT_HW_C2
#include "maxPool_layer2.h"     // CHANNELS_P2, OUT_HW_P2
#include "flatten.h"            // IN_SIZE_FL
#include "dense_layer1.h"       // IN_D1, OUT_D1
#include "dense_layer2.h"       // OUT_D2

/* buffers with layer‑specific sizes */
static float img_buf[IN_CH][IN_HW][IN_HW];
static float fm1[OUT_CH][OUT_HW][OUT_HW];                   // 28×28×32
static float pl1[CHANNELS_P1][OUT_HW_P1][OUT_HW_P1];        // 14×14×32
static float fm2[OUT_CH_C2][OUT_HW_C2][OUT_HW_C2];          // 10×10×32
static float pl2[CHANNELS_P2][OUT_HW_P2][OUT_HW_P2];        //  5× 5×32
static float vec[IN_D1];                                    // 800     
static float hid[OUT_D1];                                   // 64      
static float logit_buf[OUT_D2];                             // 43      


// AXI pragmas (no new names) 
#pragma HLS INTERFACE m_axi      port=img     offset=slave bundle=gmem0
#pragma HLS INTERFACE m_axi      port=logits  offset=slave bundle=gmem1
#pragma HLS INTERFACE s_axilite  port=img                   bundle=ctrl
#pragma HLS INTERFACE s_axilite  port=logits                bundle=ctrl
#pragma HLS INTERFACE s_axilite  port=return                bundle=ctrl

#pragma HLS DATAFLOW  
void cnn_top(const float *img, float *logits) {
    // Copy images into BRAM (3x32x32)
    COPY_IN: for (int c = 0; c < IN_CH;  c++) {
                for (int y = 0; y < IN_HW; y++) {
                    for (int x = 0; x < IN_HW; x++) {
                    #pragma HLS PIPELINE II=1
                    img_buf[c][y][x] = img[c*IN_HW*IN_HW + y*IN_HW + x];
                }
            }
        }
        
        conv1( img_buf , fm1 );
        pool1( fm1 , pl1 );
        conv2( pl1 , fm2 );
        pool2( fm2 , pl2 );
        flatten( pl2 , vec );
        dense1 ( vec , hid );
        dense2 ( hid , logit_buf );

    // Copy Images back
    COPY_OUT: for (int i = 0; i < OUT_D2; i++) {
                #pragma HLS PIPELINE II=1
                logits[i] = logit_buf[i];
            }
}

