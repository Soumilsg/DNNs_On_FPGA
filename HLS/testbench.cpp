#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "cnn_top.h"       

static void read_buffer_from_file(const char *filename, float *buffer, size_t count) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: 1");
        exit(EXIT_FAILURE);
    }
    size_t read = fread(buffer, sizeof *buffer, count, file);
    if (read != count) {
        fprintf(stderr, "Error: 2");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fclose(file);
}

int main() {
    const size_t IMG_SIZE   = IN_CH*IN_HW*IN_HW;   
    const size_t LOGIT_SIZE = OUT_CL_TOP;         

    float *img_buf   = (float*) malloc(sizeof(float)*IMG_SIZE);
    float  logits[OUT_CL_TOP];

    read_or_die("input_image.bin", img_buf, IMG_SIZE);

    cnn_top(img_buf, logits);

    int   best_id  = 0;
    float best_val = logits[0];

    for (int k = 1; k < OUT_CL_TOP; k++){
        if (logits[k] > best_val){
            best_val = logits[k];
            best_id  = k;
        }
    }

    printf("Top class ID  = %d\n",  best_id);
    printf("Raw logit     = %.6f\n", best_val);
    printf("Done.\n");
    return 0;
}
