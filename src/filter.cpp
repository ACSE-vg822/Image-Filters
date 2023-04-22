// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#include <iostream>
#include "./../include/filter.h"
using namespace std;


// Constructor with a preloaded image
Filter::Filter() {};
Filter::~Filter() {};

// Apply the grayscale filter
Image Filter::greyScale(Image& im){
//===================================================================================
// This function convert an RGB image to grayscale.
// Input: im: Image object
// Output: Image object
//===================================================================================

    // Determines the existence of the alpha channel
    bool existsAlpha = im.existsAlpha();

    // Determines the number of output channels for
    // the filtered image based on number of channels:
    //     N=#comp     components
    //       1           grey
    //       2           grey, alpha
    //       3           red, green, blue
    //       4           red, green, blue, alpha
    int outChannels = existsAlpha ? 2 : 1;
    int w = im.getWidth();
    int h = im.getHeight();
    int c = im.getChannels();
    // Allocate memory for the filtered image
    unsigned char* res = new unsigned char[w * h * outChannels];

    // Grey scale filter
    unsigned char grey;
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
        {
            // Indexing
            int index = (i * w + j) * c;        // 1D input array
            int indexOut = (i * w + j) * outChannels; // 1D output array

            // Read the pixel data according to the stbi documentation
            if (c <= 2)
                grey = im.getPixels()[index];
            else if (c > 2)
            {
                double red = im.getPixels()[index];
                double green = im.getPixels()[index + 1];
                double blue = im.getPixels()[index + 2];
                grey = (unsigned char)(0.299 * red + 0.587 * green + 0.114 * blue);
            }

            // Write the grey filter
            res[indexOut] = grey;

            // Keep the alpha channel if exists
            if (existsAlpha)
            {
                unsigned char alpha = im.getPixels()[index + c - 1];
                res[indexOut + 1] = alpha;
            }
        }

    // char *output = "../Output/test.png";
    return Image(w, h, outChannels,
                res, im.getFilename());
};

//Vidushee:
//This function takes an image object "im" and balances the its colors.
//Then returns a new image with balanced colors.
Image Filter::autoColorBalance(Image& im) {
// ================================================================================================
// This function balances the color of an image.
// Input: im: Image object
// Output: Image object
// =================================================================================================
    
    //getting dimensions and channels of input image
    int w = im.getWidth();
    int h = im.getHeight();
    int c = im.getChannels();
    
    //allocate memory for output image
    unsigned char* res = new unsigned char[w * h * c];

    //saving the total number of pixels for the image
    bool existsAlpha = im.existsAlpha();

    //declaring variables to store the values of average intensities of each channel,scaling factors and
    //overall average intensities
    double total_pixels = w * h; //saving number of pixels for the image
    double red_avg, red_scale, green_avg, green_scale, blue_avg, blue_scale, avg_intensity;
    
    //this variable will keep a record of pixel index when we iterate over the 1D array of image using nested loops
    int pixel_idx;

    //checking if the image has multiple color channels
    if (c <= 2) {
        cout << "Image doesn't have multiple colors to balance!!!!!!";
        return Image(w, h, c, im.getPixels(), im.getFilename());
    }

    //calculating the sum of red, green and blue intensities of each pixel
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pixel_idx = (j * w + i) * c;
            red_avg += im.getPixels()[pixel_idx + 0];   //red
            green_avg += im.getPixels()[pixel_idx + 1]; //green
            blue_avg += im.getPixels()[pixel_idx + 2];  //blue
        }
    }
    
    //calculating the average intensities of each channel by diving respective sums by total pixel count
    red_avg = red_avg / total_pixels;
    green_avg = green_avg / total_pixels;
    blue_avg = blue_avg / total_pixels;
    avg_intensity = (red_avg + green_avg + blue_avg) / 3.0;

    //calculate the scaling factor for each channel
    red_scale = avg_intensity / red_avg;
    green_scale = avg_intensity / green_avg;
    blue_scale = avg_intensity / blue_avg;
    
    //scaling the color values of each pixel by mutiplying them with repective scaling factors
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
             pixel_idx = (j * w + i) * c;
             res[pixel_idx + 0] = min(255, static_cast<int>(im.getPixels()[pixel_idx + 0] * red_scale));
             res[pixel_idx + 1] = min(255, static_cast<int>(im.getPixels()[pixel_idx + 1] * green_scale));
             res[pixel_idx + 2] = min(255, static_cast<int>(im.getPixels()[pixel_idx + 2] * blue_scale));

             //if the input image has an alpha channel then copy it over to the output 
             if (existsAlpha) {
                res[pixel_idx + 3] = min(255, static_cast<int>(im.getPixels()[pixel_idx + 3]));
             }
        }
    }
    
    //create and return a new image object with the balanced colors
    return Image(w, h, c, res, im.getFilename());
};

Image Filter::brightness(Image& im, int bright_value, bool is_auto) {
// =================================================================================================================
// This function generates a new image after adjusting the brightness of the input image.
// Input: im: input image
//        bright_value: brightness value to adjust
//        is_auto: whether to apply auto brightness filter
// Output: Image after adjusting the brightness
// =================================================================================================================
   
    int im_w = im.getWidth();
    int im_h = im.getHeight();
    int chanel_size = im.getChannels();
    // Error handling
    if (bright_value != 0 && is_auto == true) {
        std::cout << "Error: Brightness value is set, but auto brightness filter is on." << std::endl;
        return Image(im_w, im_h, chanel_size, im.getPixels(), im.getFilename());
    }
    else if (bright_value == 0 && is_auto == false) {
        std::cout << "Error: Brightness value is not set, but auto brightness filter is off." << std::endl;
        return Image(im_w, im_h, chanel_size, im.getPixels(), im.getFilename());
    }
    else if (bright_value < -255 || bright_value > 255) {
        std::cout << "Error: Brightness value is out of range." << std::endl;
        return Image(im_w, im_h, chanel_size, im.getPixels(), im.getFilename());
    }

    // Adjust brightness
    else {
        // Allocate memory for the filtered image
        unsigned char* res = new unsigned char[im_w * im_h * chanel_size];

        // Determines the existence of the alpha channel
        bool existsAlpha = im.existsAlpha();

        // Determines the number of channels need to adjust
        //     N=#comp     components
        //       1           grey
        //       2           grey, alpha
        //       3           red, green, blue
        //       4           red, green, blue, alpha
        int Channels = chanel_size <= 2 ? 1 : 3;

        int numPixels = im_w * im_h;
        double sum = 0;
        int index = 0;

        // Auto brightness filter
        if (is_auto) {
            // Calculate the sum of all pixels in gray or RGB channels
            for (int c = 0; c < Channels; ++c) {
                for (int i = 0; i < im_h; ++i) {
                    for (int j = 0; j < im_w; ++j) {
                        index = c + im_w * chanel_size * i + chanel_size * j;
                        sum += im.getPixels()[index];
                    }
                }
            }
            // Calculate the average value
            double average = sum / (numPixels * Channels);
            // Calculate the brightness adjustment value
            bright_value = 128 - average;
        }


        // Apply brightness filter
        for (int c = 0; c < chanel_size; ++c) {
            for (int i = 0; i < im_h; ++i) {
                for (int j = 0; j < im_w; ++j) {
                    index = c + im_w * chanel_size * i + chanel_size * j;
                    // Keep the alpha channel if exists
                    if (existsAlpha && (chanel_size == c + 1)) {
                        unsigned char alpha = im.getPixels()[index];
                        res[index] = alpha;
                    }
                    // Adjust the brightness
                    else {
                        int new_value = (im.getPixels()[index] + bright_value);
                        res[index] = std::max(0, std::min(new_value, 255));
                    }
                }
            }
        }

        return Image(im_w, im_h, chanel_size, res, im.getFilename());
    }
};

Image Filter::histogramEqualization(Image& im) {
// ==============================================================================================================
// This function generates a new image after applying histogram equalization to the input image.
// Input: im: input image
// Output: Image after applying histogram equalization
// ================================================================================================================
    int w = im.getWidth();
    int h = im.getHeight();
    int c = im.getChannels();
    unsigned char* res = new unsigned char[w * h * c];
    int outChannels = c;
    bool existsAlpha = im.existsAlpha();
    // Determines the number of output channels for
    // the filtered image based on number of channels:
    //     N=#comp     components
    //       1           grey
    //       2           grey, alpha
    //       3           red, green, blue
    //       4           red, green, blue, alpha
    
    //variable to keep track of pixel index while traversing the image(1D array) 
    int pixel_idx;
    double total_pixels = w * h;

    //initializing histogram with 256 elements(0 to 255) all initialized to 0
    vector<double> hist(256, 0);
    //initializing cumulative distribution function with 256 elements(0 to 255) all initialized to 0
    vector<double> cdf(256, 0);

    //equalization for greyscale image
    if(c <= 2) {
        
        //populate the histogram with number of occurences of each element in the image
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                pixel_idx = (j * w + i) * c;
                //unsigned char intensity = this->data[pixel_idx];
                hist[im.getPixels()[pixel_idx]]++;
            }
        }

        //populating cdf
        cdf[0] = hist[0];
        for (int i = 1; i < 256; i++) {
            cdf[i] = cdf[i - 1] + hist[i];
        }

        //applying equalization
        //loop through each row
        for (int j = 0; j < h; j++) {

            //loop through each column
            for (int i = 0; i < w; i++) {

                //calculate current pixel pixel index in the 1D array(row major form)
                pixel_idx = (j * w + i) * c;

                //intensity of current pixel
                unsigned char intensity = im.getPixels()[pixel_idx];

                //calculate the equalized intensity using CDF
                unsigned char equalized_intensity = static_cast<unsigned char>(round(255.0 * cdf[intensity] / (w * h)));
                
                //set the equalized intensity in the result image
                res[pixel_idx] = equalized_intensity;

                //if the input image has an alpha channel then copy it over to the output
                if (existsAlpha) {
                    res[pixel_idx + 1] = im.getPixels()[pixel_idx + 1];
                }
            }
        }
    }
    
    //equalization for color image
    if (c > 2) {
        //converting to YCbCr color space so we can play with luminance
        vector<unsigned char> ycbcr_data(h * w * c);
                
        for (int j = 0; j < h; j++) {
            for (int i = 0; i < w; i++) {
                pixel_idx = (j * w + i) * c;

                // saving respective channel data
                double r = static_cast<double>(im.getPixels()[pixel_idx + 0]);
                double g = static_cast<double>(im.getPixels()[pixel_idx + 1]);
                double b = static_cast<double>(im.getPixels()[pixel_idx + 2]);

                //converting from rgb to ycbcr
                double y = 0.299 * r + 0.587 * g + 0.114 * b;
                double cb = -0.169 * r - 0.331 * g + 0.500 * b + 128.0;
                double cr = 0.500 * r - 0.419 * g - 0.081 * b + 128.0;

                //making sure ycbcr data has values between 0 and 255
                ycbcr_data[pixel_idx + 0] = static_cast<unsigned char>(y);
                ycbcr_data[pixel_idx + 1] = static_cast<unsigned char>(cb);
                ycbcr_data[pixel_idx + 2] = static_cast<unsigned char>(cr);

                //if alpha channel exists simply copy over the data 
                if (existsAlpha) {
                    ycbcr_data[pixel_idx + 3] = im.getPixels()[pixel_idx + 3];
                }
                hist[ycbcr_data[pixel_idx + 0]]++;
            }
        }
        //histogram equalization on the Y channel
        //populating cdf
        cdf[0] = hist[0];
        for (int i = 1; i < 256; i++) {
            cdf[i] = cdf[i - 1] + hist[i];
        }

        //finding minmum value from cdf
        double cdf_min = cdf[0];
        for (int i = 0; i < 256; i++) {
            if (cdf[i] < cdf_min) {
                cdf_min = cdf[i];
            }
        }

        //Applying equalization to the Y(luminance) channel of the YCbCr color space
        //loop through each row
        for (int j = 0; j < h; j++) {

            //loop through each column
            for (int i = 0; i < w; i++) {

                //calculate current pixel pixel index in the 1D array(row major form)
                pixel_idx = (j * w + i) * c;

                //calculate the new equalized Y value intensity using CDF
                double newY = ((cdf[ycbcr_data[pixel_idx + 0]] - cdf_min) / (total_pixels - cdf_min)) * 255;
                
                //set the new equalized Y value in the YCbCr data
                ycbcr_data[pixel_idx + 0] = static_cast<unsigned char>(newY);
            }
        }

        // converting back to rgb
         //loop through each row
        for (int j = 0; j < h; j++) {

            //loop through each column
            for (int i = 0; i < w; i++) {

                //calculate current pixel pixel index in the 1D array(row major form)
                pixel_idx = (j * w + i) * c;

                //retrieve the Y, Cb, Cr values from ycbcr data 
                double y = static_cast<double>(ycbcr_data[pixel_idx + 0]);
                double cb = static_cast<double>(ycbcr_data[pixel_idx + 1]) - 128.0;
                double cr = static_cast<double>(ycbcr_data[pixel_idx + 2]) - 128.0;

                //converting ycbcr back to RGB
                double r = y + 1.402 * cr;
                double g = y - 0.344 * cb - 0.714 * cr;
                double b = y + 1.772 * cb;

                //clamp the RGB values between 0 and 255
                res[pixel_idx + 0] = static_cast<unsigned char>(min(255.0, (max(0.0, r))));
                res[pixel_idx + 1] = static_cast<unsigned char>(min(255.0, (max(0.0, g))));
                res[pixel_idx + 2] = static_cast<unsigned char>(min(255.0, (max(0.0, b))));

                //if alpha channel exists simply copy over the data 
                if (existsAlpha) {
                    res[pixel_idx + 3] = im.getPixels()[pixel_idx + 3];
                }
            }
        }
    }
    return Image(w, h, outChannels, res, im.getFilename());
};

Image Filter::median_blur(Image& im, int kernel_size) {
// ==============================================================================================================
// This function apply median blur to the input image
// Input: im: input image
//        kernel_size: kernel size(e.g 3x3, kernel_size = 3)
// Output: Image: output image
// ==============================================================================================================
 
    int im_w = im.getWidth();
    int im_h = im.getHeight();
    int chanel_size = im.getChannels();
    bool is_alpha = im.existsAlpha();

    unsigned char* res = median_blur_loop_3d(im.getPixels(), kernel_size, chanel_size, im_w, im_h, 1, is_alpha);

    return Image(im_w, im_h, chanel_size, res, im.getFilename());
};

Image Filter::box_blur(Image& im, const int kernel_size) {
// ==============================================================================================================
// This function apply box blur to the input image
// Input: im: input image
//        kernel_size: kernel size(e.g 3x3, kernel_size = 3)
// Output: Image: output image
// ==============================================================================================================

    int w = im.getWidth();
    int h = im.getHeight();
    int c = im.getChannels();
    bool existsAlpha = im.existsAlpha();

    // generate box kernel
    std::vector<std::vector<double>> ker = ker_tool.box_kernel(kernel_size);
    int size = c*w*h;
    // cast the unsigned char to double, make the mathmatical calculation more accurate
    double* input = conv_tool.cast_unsChar2double(im.getPixels(), size);
    // apply 2d convolution
    double* result_temp = conv_tool.conv_2d(input, ker, c, 
                                w, h, kernel_size, kernel_size, existsAlpha);
    // cast the result to unsigned char
    unsigned char* result = conv_tool.cast_double2unsChar(result_temp, size);

    // delete temp arrays
    delete[] input;
    delete[] result_temp;

    // return result image
    return Image(w, h, c, result, im.getFilename());
};

Image Filter::gaussian_blur(Image& im, const int kernel_size, const double sigma) {
// ==============================================================================================================
// This function apply gaussian blur to the input image
// Input: im: input image
//        kernel_size: kernel size(e.g 3x3, kernel_size = 3)
// Output: Image: output image
// ==============================================================================================================

    int w = im.getWidth();
    int h = im.getHeight();
    int c = im.getChannels();
    bool existsAlpha = im.existsAlpha();

    // generate gaussian kernel
    std::vector<std::vector<double>> ker = ker_tool.gaussian_kernel(kernel_size, sigma);
    int size = c*w*h;
    // cast the unsigned char to double, make the mathmatical calculation more accurate
    double* input = conv_tool.cast_unsChar2double(im.getPixels(), size);
    // apply 2d convolution
    double* result_temp = conv_tool.conv_2d(input, ker, c, 
                                w, h, kernel_size, kernel_size, existsAlpha);
    // cast the result to unsigned char
    unsigned char* result = conv_tool.cast_double2unsChar(result_temp, size);

    // delete temp arrays
    delete[] input;
    delete[] result_temp;

    // return result image
    return Image(w, h, c, result, im.getFilename());
};

Image Filter::robert_cross_ed(Image& im, const char* blur_name, const int blur_kernel_size, const double num) {
// ==============================================================================================================
// This function apply robert cross edge detection to the input image
// Input: im: input image
//        blur_name: blur name(e.g box, gaussian)
//        blur_kernel_size: blur kernel size(e.g 3x3, kernel_size = 3)
//        num: if the blur name is gaussian, this is the sigma; otherwise, it is not uesed(=0).
// Output: Image: output image
// ==============================================================================================================

    // get the kernels for both x and y directions
    pair<vector<vector<double>>, vector<vector<double>>> kers = ker_tool.robert_cross_kernel();

    int w = im.getWidth();
    int h = im.getHeight();
    int c = im.getChannels();
    bool existsAlpha = im.existsAlpha();

    if (existsAlpha) c = 2;
    else c = 1;

    unsigned char* res = get_edge_image(im, kers, blur_name, blur_kernel_size, num);
    return Image(w, h, c, res, im.getFilename());
};

Image Filter::scharr_ed(Image& im, const char* blur_name, const int blur_kernel_size, const double num) {
// ==============================================================================================================
// This function apply scharr edge detection to the input image
// Input: im: input image
//        blur_name: blur name(e.g box, gaussian)
//        blur_kernel_size: blur kernel size(e.g 3x3, kernel_size = 3)
//        num: if the blur name is gaussian, this is the sigma; otherwise, it is not uesed(=0).
// Output: Image: output image
// ==============================================================================================================

    // get the kernels for both x and y directions
    pair<vector<vector<double>>, vector<vector<double>>> kers = ker_tool.scharr_kernel();

    int w = im.getWidth();
    int h = im.getHeight();
    int c = im.getChannels();
    bool existsAlpha = im.existsAlpha();

    if (existsAlpha) c = 2;
    else c = 1;

    unsigned char* res = get_edge_image(im, kers, blur_name, blur_kernel_size, num);
    return Image(w, h, c, res, im.getFilename());
};

Image Filter::sobel_ed(Image& im, const char* blur_name, const int blur_kernel_size, const double num) {
// ==============================================================================================================
// This function apply sobel edge detection to the input image
// Input: im: input image
//        blur_name: blur name(e.g box, gaussian)
//        blur_kernel_size: blur kernel size(e.g 3x3, kernel_size = 3)
//        num: if the blur name is gaussian, this is the sigma; otherwise, it is not uesed(=0).
// Output: Image: output image
// ==============================================================================================================

    // get the kernels for both x and y directions
    pair<vector<vector<double>>, vector<vector<double>>> kers = ker_tool.sobel_kernel();

    int w = im.getWidth();
    int h = im.getHeight();
    int c = im.getChannels();
    bool existsAlpha = im.existsAlpha();

    if (existsAlpha) c = 2;
    else c = 1;

    unsigned char* res = get_edge_image(im, kers, blur_name, blur_kernel_size, num);
    return Image(w, h, c, res, im.getFilename());
};

Image Filter::prewitt_ed(Image& im, const char* blur_name, const int blur_kernel_size, const double num) {
// ==============================================================================================================
// This function apply prewitt edge detection to the input image
// Input: im: input image
//        blur_name: blur name(e.g box, gaussian)
//        blur_kernel_size: blur kernel size(e.g 3x3, kernel_size = 3)
//        num: if the blur name is gaussian, this is the sigma; otherwise, it is not uesed(=0).
// Output: Image: output image
// ==============================================================================================================

    // get the kernels for both x and y directions
    pair<vector<vector<double>>, vector<vector<double>>> kers = ker_tool.prewitt_kernel();

    int w = im.getWidth();
    int h = im.getHeight();
    int c = im.getChannels();
    bool existsAlpha = im.existsAlpha();

    if (existsAlpha) c = 2;
    else c = 1;

    unsigned char* res = get_edge_image(im, kers, blur_name, blur_kernel_size, num);
    return Image(w, h, c, res, im.getFilename());
};

unsigned char* Filter::get_edge_image(Image& im, pair<vector<vector<double>>, vector<vector<double>>> kers, 
    const char* blur_name, const int blur_kernel_size, const double num) {
// =========================================================================================================================
// This function prepares the image for doing edge detection(convert to gray scale, then apply blur)
// Input: im: input image
//        kers: kernels for both x and y directions
//        blur_name: blur name(e.g box, gaussian)
//        blur_kernel_size: blur kernel size(e.g 3x3, kernel_size = 3)
//        num: if the blur name is gaussian, this is the sigma; otherwise, it is not uesed(=0).
// Output: unsigned char array
// ==========================================================================================================================
    
    Image im_gray = greyScale(im);
    Image im_gray_blur = blur(im_gray, blur_name, blur_kernel_size, num);

    int res_size = im_gray_blur.getChannels()* im_gray_blur.getHeight() * im_gray_blur.getWidth();
    // cast the unsigned char to double, make the mathmatical calculation more accurate
    double* input = conv_tool.cast_unsChar2double(im_gray_blur.getPixels(), res_size);
    int kernel_size = kers.first.size();
    std::cout<< kernel_size << std::endl;
    double* result1 = conv_tool.conv_2d(input, kers.first, im_gray_blur.getChannels(), 
                                im_gray_blur.getWidth(), im_gray_blur.getHeight(), kernel_size, kernel_size, im.existsAlpha());
    double* result2 = conv_tool.conv_2d(input, kers.second, im_gray_blur.getChannels(), 
                                im_gray_blur.getWidth(), im_gray_blur.getHeight(), kernel_size, kernel_size, im.existsAlpha());

    // create the result array in the heap, delete is handled by Filter class destructor.
    double* res = new double[res_size];
    // index for the result 1d array
    int res_index = 0;
    // for each chanel of the image
    for (int c = 0; c < im_gray_blur.getChannels(); ++c) {
        // for each row of the image
        for (int i = 0; i < im_gray_blur.getHeight(); ++i) {
            // for each col of the image
            for (int j = 0; j < im_gray_blur.getWidth(); ++j) {
                // get the index of an corresponding element in a 1d array, it transforms 3d-i&j&z to a 1d-index
                res_index = c + (im_gray_blur.getWidth() * im_gray_blur.getChannels() * i) + (im_gray_blur.getChannels() * j);
                if (im.existsAlpha() && (im_gray_blur.getChannels() == c+1)) res[res_index] = result1[res_index];
                else {
                    res[res_index] = sqrt(result1[res_index]*result1[res_index] + 
                        result2[res_index]*result2[res_index]);
                }
            }
        }
    }
    
    unsigned char* res_casted = conv_tool.cast_double2unsChar(res, res_size);
    unsigned char* res_casted_sorted = new unsigned char[res_size];

    delete result1;
    delete result2;
    delete res;

    return res_casted;
};

Image Filter::blur(Image& im, const char* blur_name=NULL, int kernel_size=0, double num=0) {
// =====================================================================================================
// This function apply blur to the input image, make a union of all the blur functions
// Input: im: input image
//        blur_name: blur name(e.g box, gaussian)
//        kernel_size: blur kernel size(e.g 3x3, kernel_size = 3)
//        num: if the blur name is gaussian, this is the sigma; otherwise, it is not uesed(=0).
// Output: Image: output image
// =====================================================================================================
    
    if (blur_name == "median_blur" && kernel_size > 0) {
        return median_blur(im, kernel_size);
    }
    else if (blur_name == "box_blur" && kernel_size > 0) {
        return box_blur(im, kernel_size);
    }
    else if (blur_name == "gaussian_blur" && kernel_size > 0 && num > 0) {
        return gaussian_blur(im, kernel_size, num);
    }
    else {
        std::cout << "wrong user input, return same image copy by blur" << std::endl;
        return Image(im);
    }
};

Image Filter::edge_detection(Image& im, const char* edge_name=NULL, const char* blur_name=NULL, 
    int blur_kernel_size=0, double num=0) {
// =====================================================================================================
// This function apply edge detection to the input image, make a union of all the edge detection functions
// Input: im: input image
//        edge_name: edge detection name(e.g robert_cross, scharr, sobel, prewitt)
//        blur_name: blur name(e.g box, gaussian)
//        blur_kernel_size: blur kernel size(e.g 3x3, kernel_size = 3)
//        num: if the blur name is gaussian, this is the sigma; otherwise, it is not uesed(=0).
// Output: Image: output image
// =====================================================================================================
    
    if (edge_name == "robert_cross") {
        return robert_cross_ed(im, blur_name, blur_kernel_size, num);
    }
    else if (edge_name == "scharr") {
        return scharr_ed(im, blur_name, blur_kernel_size, num);
    }
    else if (edge_name == "sobel") {
        return sobel_ed(im, blur_name, blur_kernel_size, num);
    }
    else if (edge_name == "prewitt") {
        return prewitt_ed(im, blur_name, blur_kernel_size, num);
    }
    else {
        std::cout << "wrong user input, return same image copy by edge_detection" << std::endl;
        return Image(im);
    }

};



void Filter::bubble_sort(vector<unsigned char>& vec, bool (*cmp)(unsigned char, unsigned char)) {
// =====================================================================================================
// This function sort the input vector in ascending order
// Input: vec: input vector
//        cmp: the comparison function
// Output: None
// =====================================================================================================
    int n = vec.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (!cmp(vec[j], vec[j+1])) {
                std::swap(vec[j], vec[j+1]);
            }
        }
    }
};


unsigned char* Filter::median_blur_loop_3d(const unsigned char* vol, int kernel_size, 
    int chanel_size, int vol_w, int vol_h, int vol_l, bool is_alpha) {
// =====================================================================================================
// This function apply median blur to the input volume
// Input: vol: input volume
//        kernel_size: blur kernel size(e.g 3x3x3, kernel_size = 3)
//        chanel_size: number of channels
//        vol_w: volume width
//        vol_h: volume height
//        vol_l: volume length
//        is_alpha: if the volume has alpha channel
// Output: output  unsigned char volume
// =====================================================================================================

    // int vol_w = vol.getWidth();
    // int vol_h = vol.getHeight();
    // int vol_l = vol.getLength();
    // int chanel_size = vol.getChannels();
    // bool is_alpha = vol.existsAlpha();

    unsigned char* res = new unsigned char[vol_w * vol_h * vol_l* chanel_size];
    int pad = kernel_size/ 2;
    
    // travserse picture
    for (int k=0; k<vol_l; ++k){
        for (int i=0; i<vol_h; ++i) {
            for (int j=0; j<vol_w; ++j) {
                // travese channel
                for (int c=0; c<chanel_size; ++c) {
                    // Calculates the index of the current pixel in the result array
                    // int res_index = k * c + vol_w * chanel_size * i + chanel_size * j;
                    int res_index = k * vol_w * vol_h * chanel_size + i * vol_w * chanel_size + j * chanel_size + c;

                    if (is_alpha && (chanel_size == c+1)){
                        res[res_index] = vol[res_index];
                    }else {
                        // create a vector，used to store the pixel
                        std::vector<unsigned char> pixel;
                        // std::vector<std::vector<int>> kernel;
                        for (int k_k = 0; k_k < kernel_size; ++k_k) {
                            for (int k_i=0; k_i<kernel_size; ++k_i) {
                                for (int k_j=0; k_j<kernel_size; ++k_j) {
                                    // caculate the current pixel's location in the orginal figure
                                    int cur_i = i+(k_i-pad);
                                    int cur_j = j+(k_j-pad);
                                    int cur_k = k+(k_k-pad);
                                    // check whether the pixel in the boundary of the original figure
                                    if (cur_i >= 0 && cur_i < vol_h && cur_j >= 0 && cur_j < vol_w && cur_k >= 0 && cur_k < vol_l) {
                                    // calculate the current index
                                    // int cur_index = c + vol_w * chanel_size * cur_i + chanel_size * cur_j;
                                    int cur_index = cur_k * vol_w * vol_h * chanel_size + cur_i * vol_w * chanel_size + cur_j * chanel_size + c;
                                    // add the pixel to the container
                                    pixel.push_back(vol[cur_index]);
                                    }
                                }
                            }
                        }
                        // caculate the medium value 
                        bubble_sort(pixel, [](unsigned char lhs, unsigned char rhs) {return (lhs < rhs);});
                        res[res_index] = pixel[pixel.size() / 2];
                    }
                }
            }
        }
    }
    // return Image(vol_w, vol_h, vol_l, chanel_size, res);
    return res;
}

Volume Filter::gaussian_blur_3d(Volume& vol, const int kernel_size, const double num) {
// ================================================================================================================
// This function apply gaussian blur filter to the input volume
// Input: vol: the input volume
//        kernel_size: blur kernel size(e.g 3x3x3, kernel_size = 3)
//        num: the standard deviation of the gaussian kernel
// Output: the output volume
// =================================================================================================================
    int w = vol.getWidth();
    int h = vol.getHeight();
    int z = vol.getTotalImages();
    int c = vol.getChannels();
    bool existsAlpha = (c % 2 == 0);

    // generate gaussian kernel
    std::vector<std::vector<std::vector<double>>> ker = ker_tool.gaussian_kernel_3d(kernel_size, num);
    int size = c*w*h*z;
    // cast the unsigned char to double, make the mathmatical calculation more accurate
    double* input = conv_tool.cast_unsChar2double(vol.getData(), size);
    // apply 2d convolution
    double* result_temp = conv_tool.conv_3d(input, ker, c, 
                                w, h, z, kernel_size, kernel_size, kernel_size, existsAlpha);
    // cast the result to unsigned char
    unsigned char* result = conv_tool.cast_double2unsChar(result_temp, size);

    // delete temp arrays
    delete input;
    delete result_temp;

    // return result image
    return Volume(w, h, c, result, vol.getFileNames());// constructor;
};

Volume Filter::median_blur_3d(Volume& vol, const int kernel_size) {
// ================================================================================================================
// This function apply median blur filter to the input volume
// Input: vol: the input volume
//        kernel_size: blur kernel size(e.g 3x3x3, kernel_size = 3)
// Output: the output volume
// =================================================================================================================
    std::cout<< "begin median blur 3d" << std::endl;
    int w = vol.getWidth();
    int h = vol.getHeight();
    int z = vol.getTotalImages();
    int c = vol.getChannels();
    bool existsAlpha = (c % 2 == 0);
    unsigned char* res = median_blur_loop_3d(vol.getData(), kernel_size, c, w, h, z, existsAlpha);

    std::cout<< "finish median blur 3d" << std::endl;
    return Volume(w, h, c, res, vol.getFileNames());
};
