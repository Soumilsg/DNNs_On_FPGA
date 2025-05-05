/**********************************************************************
 *  tb_cnn_top.cpp – one‑image classification test
 *
 *  Files required next to the executable:
 *      input_image.bin   – 3072 floats (3×32×32, Channel‑Height‑Width)
 *
 *  Build / run inside Vitis HLS:
 *      > csim_design
 *********************************************************************/
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include "cnn_top.h"          /* declares cnn_top()          */

/* ------------------------------------------------------------------*
 *  Local helpers
 * -----------------------------------------------------------------*/
static void read_or_die(const char *fname, float *buf, size_t n)
{
    FILE *f = fopen(fname, "rb");
    if (!f){ printf("Cannot open %s\n", fname); std::exit(1); }
    if (fread(buf, sizeof(float), n, f) != n){
        printf("File %s has wrong length\n", fname); std::exit(1);
    }
    fclose(f);
}

int main()
{
    /* ------------- allocate input & output buffers -------------- */
    const size_t IMG_SIZE   = IN_CH*IN_HW*IN_HW;   /* 3072 */
    const size_t LOGIT_SIZE = OUT_CL_TOP;          /* 43   */

    float *img_buf   = (float*) malloc(sizeof(float)*IMG_SIZE);
    float  logits[OUT_CL_TOP];

    /* ------------- read one test image -------------------------- */
    read_or_die("input_image.bin", img_buf, IMG_SIZE);

    /* ------------- run the accelerator -------------------------- */
    cnn_top(img_buf, logits);

    /* ------------- find arg‑max --------------------------------- */
    int   best_id  = 0;
    float best_val = logits[0];

    for (int k = 1; k < OUT_CL_TOP; k++){
        if (logits[k] > best_val){
            best_val = logits[k];
            best_id  = k;
        }
    }

    /* ------------- report result -------------------------------- */
    printf("Top class ID  = %d\n",  best_id);
    printf("Raw logit     = %.6f\n", best_val);
    printf("Done.\n");
    return 0;
}
