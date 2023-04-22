// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#include "./../include/kernels.h"

using namespace std;

const double Kernels::pi_fun() 
{ 
// ===============================================================================
//  This function returns the value of pi
//  Input: None
//  Output: pi
// ===============================================================================
    return atan(1)*4; 
}

// generate a box kernel
vector<vector<double>> Kernels::box_kernel(int size)
{
//==============================================================================
//  This function generates a box kernel
//  Input: size of the kernel(e.g 3x3, 5x5, Input: 3 or 5)
//  Output: a 2D array of the kernel
//==============================================================================

    // define a 2D array
    vector<vector<double>> kernel(size, vector<double>(size));

    // generate the kernel
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            kernel[i][j] = 1.0/(size*size);
        }
    }
    return kernel;
}

// generate a gaussian kernel
vector<vector<double>> Kernels::gaussian_kernel(int size, double sigma)
{
//=====================================================================================
//  This function generates a gaussian kernel
//  Input: size: size of the kernel(e.g 5x5, 7x7, Input: 5 or 7)
//         sigma: standard deviation
//  Output: a 2D array of the kernel
//=====================================================================================
   // define a 2D array
    vector<vector<double>> kernel(size, vector<double>(size));
    double sum = 0.0;
    int center = size / 2;
    double pi = pi_fun();

    // generate the kernel
    for (int i = - center; i <= center; i++)
    {
        for (int j = - center; j <= center; j++)
        {
            kernel[i + center][j + center] = exp(-(i * i + j * j) / (2 * sigma * sigma)) / (2 * pi * sigma * sigma);
            sum += kernel[i + center][j + center];
        }
    }

    // normalize the kernel
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            kernel[i][j] /= sum;
        }
    }
    return kernel;
}

vector<vector<vector<double>>> Kernels::gaussian_kernel_3d(int size, double sigma)
{
//=====================================================================================
//  This function generates a gaussian kernel
//  Input: size: size of the kernel(e.g 5x5x5, 7x7x7, Input: 5 or 7)
//         sigma: standard deviation
//  Output: a 3D array of the kernel
//=====================================================================================
   // define a 3D array
    vector<vector<vector<double>>> kernel(size, vector<vector<double>>(size, vector<double>(size)));
    double sum = 0.0;
    int center = size / 2;
    double pi = pi_fun();

    // generate the kernel
    for (int i = - center; i <= center; i++)
    {
        for (int j = - center; j <= center; j++)
        {
            for (int k = - center; k <= center; k++){
                kernel[i + center][j + center][k + center] = exp(-(i * i + j * j) / (2 * sigma * sigma)) / (2 * pi * sigma * sigma);
                sum += kernel[i + center][j + center][k + center];
            }

        }
    }

    // normalize the kernel
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                kernel[i][j][k] /= sum;
            }
        }
    }
    return kernel;
}

pair<vector<vector<double>>, vector<vector<double>>> Kernels::robert_cross_kernel() {
// =========================================================================================
// This function generates a robert cross kernel
// Input: None
// Output: a pair of 2D array of the kernel
// =========================================================================================

    // generate a sobel kernel
    // define a 2D array
    vector<vector<double>> robert_cross_x(2, vector<double>(2));
    vector<vector<double>> robert_cross_y(2, vector<double>(2));

    // generate the sobel kernel
    robert_cross_x = {{1, 0},
                      {0, -1}};
    robert_cross_y = {{0, 1},
                      {-1, 0}};

    return make_pair(robert_cross_x, robert_cross_y);
}

pair<vector<vector<double>>, vector<vector<double>>> Kernels::scharr_kernel() {
// ==================================================================================
//  This function generates a scharr kernel
// Input: None
// Output: a pair of 2D array of the kernel
// ==================================================================================
 
    // define a 2D array
    vector<vector<double>> Scharr_x(3, vector<double>(3));
    vector<vector<double>> Scharr_y(3, vector<double>(3));

    // generate the sobel kernel
    Scharr_x = {{3 , 0, -3},
                {10, 0, -10},
                {3 , 0, -3}};
    Scharr_y = {{3 , 10, 3},
                {0 , 0, 0},
                {-3, -10, -3}};
    
    return make_pair(Scharr_x, Scharr_y);
}

pair<vector<vector<double>>, vector<vector<double>>> Kernels::sobel_kernel() {
// ==================================================================================
//  This function generates a sobel kernel
// Input: None
// Output: a pair of 2D array of the kernel
// ==================================================================================

    // define a 2D array
    vector<vector<double>> sobel_x(3, vector<double>(3));
    vector<vector<double>> sobel_y(3, vector<double>(3));

    // generate the sobel kernel
    sobel_x = {{1 , 0, -1},
               {2 , 0, -2},
               {1 , 0, -1}};
    sobel_y = {{1 , 2, 1},
               {0 , 0, 0},
               {-1, -2, -1}};
    return make_pair(sobel_x, sobel_y);
}
        
pair<vector<vector<double>>, vector<vector<double>>> Kernels::prewitt_kernel() {
// ==================================================================================
// it generate a prewitt kernel
// Input: None
// Output: a pair of 2D array of the kernel
// ==================================================================================

    // define a 2D array
    vector<vector<double>> Prewitt_x(3, vector<double>(3));
    vector<vector<double>> Prewitt_y(3, vector<double>(3));

    // generate the sobel kernel
    Prewitt_x = {{1 , 0, -1},
                 {1 , 0, -1},
                 {1 , 0, -1}};
    Prewitt_y = {{1 , 1, 1},
                 {0 , 0, 0},
                 {-1, -1, -1}};
    
    return make_pair(Prewitt_x, Prewitt_y);

}

