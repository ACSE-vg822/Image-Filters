// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#include "./../include/conv_tool.h"
# include <iostream>

ConvTool::ConvTool() {}

ConvTool::~ConvTool() {}

double* ConvTool::conv_2d(const double* im, std::vector<std::vector<double>> kernel, int chanel_size, 
                    int im_w, int im_h, int k_w, int k_h, bool is_alpha) {
// =========================================================================================================================
//  This function performs 2D image convolution
//  Input:  im: a 1D array of the image
//          kernel: a 2D array of the kernel
//          chanel_size: the number of channels of the image
//          im_w: the width of the image
//          im_h: the height of the image
//          k_w: the width of the kernel
//          k_h: the height of the kernel
//          is_alpha: whether the image has alpha channel
//  Output: a 1D array of the result
// =========================================================================================================================
    
    std::vector<std::vector<std::vector<double>>> fake_3d_kernel = {kernel};
    double* res = conv_3d(im, fake_3d_kernel, chanel_size, im_w, im_h, 1, k_w, k_h, 1, is_alpha);
    return res;
}

double* ConvTool::conv_3d(const double* vol, std::vector<std::vector<std::vector<double>>> kernel, int chanel_size, 
            int vol_w, int vol_h, int vol_d, int k_w, int k_h, int k_d, bool is_alpha) {
// =========================================================================================================================
//  This function performs 3D image convolution
//  Input:  im: a 1D array of the image
//          kernel: a 2D array of the kernel
//          chanel_size: the number of channels of the image
//          vol_w: the width of the image
//          vol_h: the height of the image
//          vol_d: the depth of the image
//          k_w: the width of the kernel
//          k_h: the height of the kernel
//          k_d: the depth of the kernel
//          is_alpha: whether the image has alpha channel
//  Output: a 1D array of the result
// =========================================================================================================================

    // creat the result 1d array, the array would be deleted in functions of Filter class
    // we can free up the space immediatly once we have casted them to unsigned char in those functions in Filter class
    // so everytime when we use convlution 3d or 2d, do delete the returned result when we do not need them anymore
    double* res = new double[vol_w * vol_h * vol_d * chanel_size];
    // num used for padding
    double pad = 0;
    // index for the result 1d array
    int res_index = 0;
    // the current index of 1d array
    int cur_index = 0;
    // the current row of the indexed number in a 3d layout
    int cur_i = 0;
    // the current col of the indexed number in a 3d layout
    int cur_j = 0;
    // the current depth of the indexed number in a 3d layout
    int cur_z = 0;
    
    
    // for each layer of the volume
    for (int z = 0; z < vol_d; ++z) {
        // for each row of the volume
        for (int i = 0; i < vol_h; ++i) {
            // for each col of the volume
            for (int j = 0; j < vol_w; ++j) {
                // for each chanel of the volume
                for (int c = 0; c < chanel_size; ++c) {
                    // get the index of an corresponding element in a 1d array, it transforms 3d-i&j&z to a 1d-index
                    res_index = c + (vol_w * vol_h * chanel_size * z) + (vol_w * chanel_size * i) + (chanel_size * j);
                    // if the 1d array has alpha, then directly assign them to the result
                    if (is_alpha && (chanel_size == c+1)) res[res_index] = vol[res_index];
                    else {
                        // do the convolution by iterate through a 3d kernel
                        for (int k_z = 0; k_z < k_d; ++k_z) {
                            for (int k_i = 0; k_i < k_h; ++k_i) {
                                for (int k_j = 0; k_j < k_w; ++k_j) {
                                    // find the corressponding pixel in a volume
                                    cur_i = i+(k_i-k_h/2);
                                    cur_j = j+(k_j-k_w/2);
                                    cur_z = z+(k_z-k_d/2);
                                    // check if the required pixel in the volume boundary (padding or real data)
                                    if(cur_i < 0 || cur_i >= vol_h || cur_j < 0 || cur_j >= vol_w || cur_z < 0 || cur_z >= vol_d){
                                        // apply if it is padding, accumulate the result to the final output array
                                        res[res_index] += kernel[k_z][k_i][k_j] * pad;
                                    }
                                    else {
                                        // apply if it is real data, accumulate the result to the final output array
                                        cur_index = c + (vol_w * vol_h * chanel_size * cur_z) + 
                                            (vol_w * chanel_size * cur_i) + (chanel_size * cur_j);
                                        res[res_index] += kernel[k_z][k_i][k_j] * vol[cur_index];
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        std::cout<<")))____)))"<< std::endl;
    }
    // return the new 1d array result
    return res;
}

unsigned char* ConvTool::cast_double2unsChar(double* input, int size) {
// ===========================================================================================
//  This function casts a 1D array of double to unsigned char
// Input:  input: a 1D array of double
//         size: the size of the array
// Output: 1D array of unsigned char
// ===========================================================================================    
    
    unsigned char* res = new unsigned char[size];
    for (int i=0; i<size; ++i) {
        res[i] = static_cast<unsigned char>(input[i]);
    }
    // delete process is in the called functions
    // or if the res is used to create Image object, it will be handled by Image class
    return res;
}

double* ConvTool::cast_unsChar2double(unsigned char* input, int size) {
// ===========================================================================================
//  This function casts a 1D array of unsigned char to double
// Input:  input: a 1D array of unsigned char
//         size: the size of the array
// Output: 1D array of double
// ===========================================================================================

    double* res = new double[size];
    for (int i=0; i<size; ++i) {
        res[i] = static_cast<double>(input[i]);
    }
    // delete process is in the called functions
    return res;
}
