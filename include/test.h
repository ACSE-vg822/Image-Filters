// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#ifndef TEST
#define TEST

#include "image.h"
#include "filter.h"
#include "volume.h"
#include "projection.h"
#include "slice.h"
#include "kernels.h"
#include "conv_tool.h"


class Test {

    public:
        Test();
        ~Test();
        
        bool test_greyScale();
        bool test_autoColorBalance(const char* filename);
        bool test_brightness();
        bool test_histogramEqualization(const char* filename);

        bool test_box_kernel();
        bool test_gaussian_kernel();
        bool test_sobel_kernel();
        bool test_prewitt_kernel();
        bool test_scharr_kernel();
        bool test_robert_cross_kernel();

        bool test_median_blur();
        bool test_box_blur();
        bool test_gaussian_blur();

        bool test_robert_cross_ed();
        bool test_scharr_ed();
        bool test_sobel_ed();
        bool test_prewitt_ed();

        bool test_chosen_projection(const char* filename);
        bool testSlice(const char *path);
};

#endif
