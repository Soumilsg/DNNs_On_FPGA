#ifndef FLATTEN_LAYER_H
#define FLATTEN_LAYER_H

#define CH_FL      32        
#define HW_FL       5   
#define IN_SIZE_FL (CH_FL*HW_FL*HW_FL) 

void flatten(const float X[CH_FL][HW_FL][HW_FL], float Y[IN_SIZE_FL]);

#endif