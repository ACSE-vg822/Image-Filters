// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#ifndef FILTER
#define FILTER

#include "image.h"
#include "volume.h"
#include "conv_tool.h"
#include "kernels.h"


class Filter
{
public:
    // Constructors
    // Uses the Image constructor and destructor so it is
    // possible to work with the same image
    // Filter(const char *filename) : Image(filename){};
    Filter();
    ~Filter(); //: ~Image(){};

    // Filters
    // 1. Color correction
    Image greyScale(Image& im);
    Image autoColorBalance(Image& im);
    Image brightness(Image& im, int bright_value=0, bool is_auto=true);
    Image histogramEqualization(Image& im);
    // 2. Image blur
    Image blur(Image& im, const char* blur_name, int kernel_size, double num);
    // 3. Edge detection
    Image edge_detection(Image& im, const char* edge_name, const char* blur_name, int blur_kernel_size, double num);

    Volume gaussian_blur_3d(Volume& vol, const int kernel_size, const double num);
    Volume median_blur_3d(Volume& vol, const int kernel_size);


private:
    ConvTool conv_tool;
    Kernels ker_tool;

    unsigned char* get_edge_image(Image& im, pair<vector<vector<double>>, vector<vector<double>>> kers, 
        const char* blur_name, const int blur_kernel_size, const double num);
    void bubble_sort(vector<unsigned char>& vec, bool (*cmp)(unsigned char, unsigned char));

    Image median_blur(Image& im, const int kernel_size);
    Image box_blur(Image& im, const int kernel_size);
    Image gaussian_blur(Image& im, const int kernel_size, const double sigma);
    
    Image robert_cross_ed(Image& im, const char* blur_name, const int blur_kernel_size, const double num);
    Image scharr_ed(Image& im, const char* blur_name, const int blur_kernel_size, const double num);
    Image sobel_ed(Image& im, const char* blur_name, const int blur_kernel_size, const double num);
    Image prewitt_ed(Image& im, const char* blur_name, const int blur_kernel_size, const double num);

    unsigned char* median_blur_loop_3d(const unsigned char* vol, int kernel_size, 
        int chanel_size, int vol_w, int vol_h, int vol_l, bool is_alpha);
};
#endif

