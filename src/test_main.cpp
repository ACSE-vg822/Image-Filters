// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#define STB_IMAGE_IMPLEMENTATION
#include "./../include/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./../include/stb_image_write.h"

# include "./../include/image.h"
# include "./../include/volume.h"
# include "./../include/filter.h"
# include "./../include/projection.h"
#include "./../include/test.h"
# include "./../include/slice.h"
# include <iostream>

int main ()
{
    Test test;
    // Test everthing
    test.test_greyScale();
    test.test_brightness();

    const char* filename = "../Images/gracehopper.png";
    test.test_autoColorBalance(filename);

    const char* filename1 = "../Images/tienshan.png";
    if (test.test_histogramEqualization(filename1)==true) {
      std::cout << "All tests passed for histogramEqualization()!" << std::endl;
    }
    else if (test.test_histogramEqualization(filename1)==false) {
        std::cout << "Some tests failed for histogramEqualization()!" << std::endl;
    }

    test.test_box_kernel();
    test.test_gaussian_kernel();
    test.test_sobel_kernel();
    test.test_prewitt_kernel();
    test.test_scharr_kernel();  
    test.test_robert_cross_kernel();

    test.test_median_blur();
    test.test_box_blur();
    test.test_gaussian_blur();

    test.test_sobel_ed();
    test.test_prewitt_ed();
    test.test_scharr_ed();
    test.test_robert_cross_ed();

    const char* filename2 = "../Images/test_images";;
    test.test_chosen_projection(filename2);

    const char *confuciusornis = "../Scans/confuciusornis";
    test.testSlice(confuciusornis);
    
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
