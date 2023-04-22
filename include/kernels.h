// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#ifndef KERNELS
#define KERNELS

#include <vector>
#include <cmath>

using namespace std;

class Kernels {
    
    public:
        virtual const double pi_fun();

        // generate a box kernel
        virtual vector<vector<double>> box_kernel(int size);
    
        // generate a gaussian kernel
        virtual vector<vector<double>> gaussian_kernel(int size, double sigma);

        virtual vector<vector<vector<double>>> gaussian_kernel_3d(int size, double sigma);

        virtual pair<vector<vector<double>>, vector<vector<double>>> robert_cross_kernel();

        virtual pair<vector<vector<double>>, vector<vector<double>>> scharr_kernel();

        virtual pair<vector<vector<double>>, vector<vector<double>>> sobel_kernel();
        
        virtual pair<vector<vector<double>>, vector<vector<double>>> prewitt_kernel();

};
#endif
