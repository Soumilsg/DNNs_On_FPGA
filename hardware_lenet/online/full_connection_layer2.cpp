

#include "full_connection_layer2.h"

void full_connection_layer2(
    float input_data_buf[INPUT_NUM1],
    float output_data_buf[OUTPUT_NUM1],
    float weights_buf[INPUT_NUM1],
    float bias_buf[OUTPUT_NUM1],
    bool active,
    int i   
)
{

        full_C_cal:
        {
            calculate:
                /* code */
                PROCESS:for (int j = 0; j < OUTPUT_NUM1; j++)
                {
    #pragma HLS PIPELINE
                    /* code */
                    output_data_buf[j] += input_data_buf[i] * weights_buf[j];
                }
        }
    
    
}
