// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#ifndef CONV_TOOL
#define CONV_TOOL

#include <vector>

class ConvTool {
    public:
        // default constructor
        ConvTool();
        
        virtual ~ConvTool();

        // 2d_convolution
        virtual double* conv_2d(const double* im, std::vector<std::vector<double>> kernel, int chanel_size, 
            int im_w, int im_h, int k_w, int k_h, bool is_alpha);
        
        virtual double* conv_3d(const double* vol, std::vector<std::vector<std::vector<double>>> kernel, int chanel_size, 
            int vol_w, int vol_h, int vol_d, int k_w, int k_h, int k_d, bool is_alpha);

        virtual unsigned char* cast_double2unsChar(double* input, int size);

        virtual double* cast_unsChar2double(unsigned char* input, int size);

};
#endif
