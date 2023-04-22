// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#include<cassert> 
#include"./../include/test.h"

Test::Test() {};
Test::~Test() {};

// ===================================================================================
// Test Colour correction Filters 
// ===================================================================================
bool Test::test_greyScale(){
  int size = 27;
  int width = 3;
  int height = 3;
  int channels = 3;

  unsigned char* image_data = new unsigned char[size];
  unsigned char* image_test = new unsigned char[9];
  
  // the input image
  for (int i = 0; i < size; ++i) {
    image_data[i] = static_cast<unsigned char>(10);
  }
  // the expected result
  for (int i = 0; i < 9; ++i) {
    image_test[i] = static_cast<unsigned char>(10);
  }

  // generate output image
  Filter filter;
  Image image_res(width, height, channels, image_data, "test");
  Image image_result = filter.greyScale(image_res);

  unsigned char* image =image_result.getPixels();

  for(int i = 0; i<9; ++i){
    // test if the result is correct
    assert(image[i] == image_test[i]);
  }

  // free memory allocated for the arrays
  delete[] image_test;

  std::cout << "The test passed for grayscale!" << std::endl;

  return true;
}

bool Test::test_brightness(){
  int size = 75;
  int width = 5;
  int height = 5;
  int channels = 3;

  unsigned char* image_data = new unsigned char[size];
  unsigned char* image_test = new unsigned char[size];
    
  for (int i = 0; i < size; ++i) {
    // the input image
    image_data[i] = static_cast<unsigned char>(i + 1);
    // the expected result
    image_test[i] = static_cast<unsigned char>(image_data[i]+10);
    }

  // generate output image
  Filter filter;
  Image image_res(width, height, channels, image_data, "test");
  Image image_result = filter.brightness(image_res, 10, false);

  unsigned char* image =image_result.getPixels();

  for(int i = 0; i<size; ++i){
    // test if the result is correct
    assert(image[i] == image_test[i]);
  }

  // free memory allocated for the arrays
  delete[] image_test;

  std::cout << "The test passed for brightness!" << std::endl;

  return true;
}

bool Test::test_autoColorBalance(const char* filename) {

    //const char* filename = "../Images/vh_anatomy.png";
    Image test_image(filename);
    int status = test_image.load();

    Filter filter;
    Image result_image = filter.autoColorBalance(test_image);

    //now validating result image dimensions vs test image dimensions
    assert(result_image.getWidth() == test_image.getWidth());
    assert(result_image.getHeight() == test_image.getHeight());
    assert(result_image.getChannels() == test_image.getChannels());

        
    //now checking if the average intensity of each channel(R, G, B) in the resulting image is equal
    int w = result_image.getWidth();
    int h = result_image.getHeight();
    int c = result_image.getChannels();
    double total_pixels = w * h;

    double avg_r = 0, avg_g = 0, avg_b = 0;

    //this variable will keep a record of pixel index when we iterate over the 1D array of image using nested loops
    int pixel_idx;
    
    //calculating the sum of red, green and blue intensities of each pixel
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pixel_idx = (j * w + i) * c;
            avg_r += result_image.getPixels()[pixel_idx + 0];//red
            avg_g += result_image.getPixels()[pixel_idx + 1];//green
            avg_b += result_image.getPixels()[pixel_idx + 2];//blue
        }
    }
    
    //calculating the average intensities of each channel by diving respective sums by total pixel count
    avg_r /= total_pixels;
    avg_g /= total_pixels;
    avg_b /= total_pixels;

    //checking if avg intensities are equal
    //tolerance is kept 1 because it is not neccessary that these 3 quantities will be exactly equal,
    //autocolorbalance changes the RGB values of pixels so they take new integer values between 0 and 255
    //such that with these new values the average intensity values are as close as possible values
    double tolerance = 1;
    assert(abs(avg_r - avg_g) < tolerance);
    assert(abs(avg_g - avg_b) < tolerance);
    assert(abs(avg_r - avg_b) < tolerance);

    //if the code reaches this line it means all assert statements have passed, hence return true
    return true;
}

//helper functions for testing histogram equalization
//this function calculates entropy for a given histogram
double calc_entropy(const std::vector<double>& hist, int num_pixels) {
    double entropy = 0; //this value will accumulate the entropy value as we iterate through the histogram
    for (int i = 0; i < 256; i++) {
        if (hist[i] > 0) { // checking if that intensity value has a non-zero frequncy in the histogram
            
            //calculating the probability of that intensity value by dividing the freqency by total pixels
            double prob = hist[i] / num_pixels;
            
            //product of probability and base-2 logarithm of the probability represents the entropy contibution of the current intensity value
            // and we add this expression to total entropy
            entropy += prob * log2(prob);
        }
    }
    //returning a negation of entropy because log2(prob) is always negative as (0 < prob <= 1)
    return -entropy;
}

//this function calculates the uniformity in histograms
//the more uniform the histogram is smaller the sum of squared differences will be
double calc_histogram_uniformity(const std::vector<double>& hist, int num_pixels) {
    
    double sum_sq_diff = 0.0;

    for (int i = 1; i < 256; i++) {
        double diff = hist[i] - hist[i-1];
        sum_sq_diff += diff * diff;
    }

    return sum_sq_diff;
}

//It is to be noted here that not all metrics will pass for every image,
//uniformization of histogram depends on the individual image properties, some images are more saturated, less sharp etc.
//the aim should be check that atleast one metric passes for all images.
bool Test::test_histogramEqualization(const char* filename) {

    int count = 0;
    Image test_image(filename);
    int status = test_image.load();

    Filter filter;
    Image result_image = filter.histogramEqualization(test_image);

    //now validating result image dimensions vs test image dimensions
    assert(result_image.getWidth() == test_image.getWidth());
    assert(result_image.getHeight() == test_image.getHeight());
    assert(result_image.getChannels() == test_image.getChannels());

    //declaring vectors to calculate histrogram and cdf for the test and result images
    std::vector<double> hist_test(256, 0);
    std::vector<double> hist_result(256, 0);
    std::vector<double> cdf_test(256, 0);
    std::vector<double> cdf_result(256, 0);

    //getting dimensions from test image
    int w = result_image.getWidth();
    int h = result_image.getHeight();
    int c = result_image.getChannels();
    
    //this variable will keep a record of pixel index when we iterate over the 1D array of image using nested loops
    int pixel_idx;

    //calculating histogram for the test and result images
    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pixel_idx = (j * w + i) * c;
            //increments the frequency count for the pixel intensity value in the respective image's histogram
            hist_test[test_image.getPixels()[pixel_idx]]++; 
            hist_result[result_image.getPixels()[pixel_idx]]++;
        }
    }

    
    double test_entropy = calc_entropy(hist_test, w * h);
    double result_entropy = calc_entropy(hist_result, w * h);
    
    //histogram equalization redistributes the pixel intensities in an image to make their distribution more uniform.
    //more uniformity leads to higher entropy, i.e., the resulting image's intensity distribution should have higher entropy,
    //this is exactly what the assert here is checking
    if (result_entropy >= test_entropy) { std::cout << "entropy test passed!" << std::endl; count++; }
    else std::cout << "entropy test failed!" << std::endl;
        

    double uniformity_test = calc_histogram_uniformity(hist_test, w * h);
    double uniformity_result = calc_histogram_uniformity(hist_result, w * h);

    // Check if the histogram of the equalized image is more uniform than the original image's histogram
    if (uniformity_test >= uniformity_result) { std::cout << "uniformity test passed!" << std::endl; count++; }
    else std::cout << "uniformity test failed!" << std::endl;
        
    

    if (count == 2)return true;
    else return false;
    
}


// ===================================================================================
// Test Blur Filters
// ===================================================================================
bool Test::test_median_blur(){
  int size = 25;
  int width = 5;
  int height = 5;
  int channels = 1;

  unsigned char* image_data = new unsigned char[size];
  unsigned char* image_test = new unsigned char[size];
    
  // the expected image
  vector<int> image_array = {4, 4, 5, 6, 7, 
                             6, 7, 8, 9, 9, 
                             11, 12, 13, 14, 14, 
                             16, 17, 18, 19, 19,
                             19, 19, 20, 21, 22};
    
  for (int i = 0; i < size; ++i) {
  // the input image
    image_data[i] = static_cast<unsigned char>(i + 1);
    image_test[i] = static_cast<unsigned char>(image_array[i]);
  }

  // generate output image
  Filter filter;
  Image image_res(width, height, channels, image_data, "test");
  Image image_result = filter.blur(image_res, "median_blur", 3, 0);


  unsigned char* image =image_result.getPixels();

  // test if the result is correct
  for(int i = 0; i<size; ++i){
    assert(image[i] == image_test[i]);
  }

  // free memory allocated for the arrays
  delete[] image_test;

  std::cout << "The test passed for median blur!" << std::endl;

  return false; 
}

bool Test::test_box_blur(){
  int size = 25;
  int width = 5;
  int height = 5;
  int channels = 1;

  unsigned char* image_data = new unsigned char[size];
  unsigned char* image_test = new unsigned char[size];
    
  // the expected image
  vector<int> image_array = {36, 48, 60, 48, 36, 
                             48, 64, 80, 64, 48, 
                             60, 80, 100, 80, 60, 
                             48, 64, 80, 64, 48, 
                             36, 48, 60, 48, 36};
    
  // the input image
  for (int i = 0; i < size; ++i) {
    image_data[i] = static_cast<unsigned char>(100);
    image_test[i] = static_cast<unsigned char>(image_array[i]);
  }

  // generate output image
  Filter filter;
  Image image_res(width, height, channels, image_data, "test");
  Image image_result = filter.blur(image_res, "box_blur", 5, 0);

  unsigned char* image =image_result.getPixels();

  // test if the result is correct
  for(int i = 0; i<size; ++i){
    assert(image[i] == image_test[i]);
  }

  // free memory allocated for the arrays
  delete[] image_test;

  std::cout << "The test passed for box blur!" << std::endl;

  return true;
}

bool Test::test_gaussian_blur(){
  int size = 25;
  int width = 5;
  int height = 5;
  int channels = 1;

  unsigned char* image_data = new unsigned char[size];
  unsigned char* image_test = new unsigned char[size];
    
  // the expected image
  vector<int> image_array = {1,2,3,4,4,
                             5,6,7,8,9,
                             10,12,12,14,14,
                             15,17,17,18,19,
                             19,20,21,22,22};
    
  // the input image
  for (int i = 0; i < size; ++i) {
      image_data[i] = static_cast<unsigned char>(i + 1);
      image_test[i] = static_cast<unsigned char>(image_array[i]);
  }

  // generate output image
  Filter filter;
  Image image_res(width, height, channels, image_data, "test");
  Image image_result = filter.blur(image_res, "gaussian_blur", 3, 0.4);

  unsigned char* image =image_result.getPixels();

  // test if the result is correct
  for(int i = 0; i<size; ++i){
    assert(image[i] == image_test[i]);
  }

  // free memory allocated for the arrays
  delete[] image_test;
    
  std::cout << "The test passed for gaussian blur!" << std::endl;

  return true;
}


// ===================================================================================
// Test Edge Detection
// ===================================================================================
bool Test::test_sobel_ed(){
  // set the figure size
  int size = 25;
  int width = 5;
  int height = 5;
  int channels = 1;

  // initialize the input and test data
  unsigned char* image_data = new unsigned char[size];
  unsigned char* image_test = new unsigned char[size];
  // the expected image
  vector<int> image_array = {17, 25, 31, 32, 27, 
                             34, 39, 41, 36, 42, 
                             52, 44, 41, 39, 60, 
                             58, 27, 8,  18, 66, 
                             55, 64, 72, 70, 65};
  // the input image 
  for (int i = 0; i < size; ++i) {
    image_data[i] = static_cast<unsigned char>(i + 1);
    image_test[i] = static_cast<unsigned char>(image_array[i]);
  }
    
  // generate output image
  Filter filter;
  Image image_res(width, height, channels, image_data, "test");

  Image image_result_box = filter.edge_detection(image_res, "sobel", "box_blur", 3, 0);

  unsigned char* image_box =image_result_box.getPixels();

  // test if the result is correct
  for(int i = 0; i<size; ++i){
    assert(image_box[i] == image_test[i]);
  }
  
  // free memory allocated for the arrays
  delete[] image_test;

  std::cout << "The test passed for sobel edge detection!" << std::endl;

  return false;
}

bool Test::test_robert_cross_ed(){
  // set the figure size
  int size = 25;
  int width = 5;
  int height = 5;
  int channels = 1;

  // initialize the input
  unsigned char* image_data = new unsigned char[size];
  unsigned char* image_test = new unsigned char[size];
    
vector<int> image_array = {1, 2, 3, 5, 5, 
                           4, 5, 6, 7, 6, 
                           8, 8, 8, 7, 8, 
                           12, 10, 7, 7, 10, 
                           12, 9, 7, 7, 10};
    
  for (int i = 0; i < size; ++i) {
    image_data[i] = static_cast<unsigned char>(i + 1);
    image_test[i] = static_cast<unsigned char>(image_array[i]);
  }
    
  // do the test
  Filter filter;
  Image image_res(width, height, channels, image_data, "test");

  Image image_result_gauss = filter.edge_detection(image_res, "robert_cross", "box_blur", 3, 0);

  unsigned char* image_gauss =image_result_gauss.getPixels();

  for(int i = 0; i<size; ++i){
    assert(image_gauss[i] == image_test[i]);
  }
  
  // free memory allocated for the arrays
  delete[] image_test;
  
  std::cout << "The test passed for robert cross edge detection!" << std::endl;

  return false;
}

bool Test::test_prewitt_ed(){
  // set the size
  int size = 25;
  int width = 5;
  int height = 5;
  int channels = 1;

  unsigned char* image_data = new unsigned char[size];
  unsigned char* image_test = new unsigned char[size];
    
  // initialize the input image
vector<int> image_array = {12, 18, 23, 23, 19, 
                           25, 28, 30, 26, 31, 
                           38, 32, 31, 29, 45, 
                           41, 19, 6, 13, 47, 
                           39, 46, 54, 50, 45};
    
  for (int i = 0; i < size; ++i) {
    image_data[i] = static_cast<unsigned char>(i + 1);
    image_test[i] = static_cast<unsigned char>(image_array[i]);
  }
    
  // do the test
  Filter filter;
  Image image_res(width, height, channels, image_data, "test");

  Image image_result_box = filter.edge_detection(image_res, "prewitt", "box_blur", 3, 0);

  unsigned char* image_box =image_result_box.getPixels();

  for(int i = 0; i<size; ++i){
    assert(image_box[i] == image_test[i]);
  }
  
  // free memory allocated for the arrays
  delete[] image_test;
    
  std::cout << "The test passed for prewitt edge detection!" << std::endl;

  return false; 
}

bool Test::test_scharr_ed(){
  // set the image size
  int size = 25;
  int width = 5;
  int height = 5;
  int channels = 1;

  unsigned char* image_data = new unsigned char[size];
  unsigned char* image_test = new unsigned char[size];
    
  // initialize the array
  vector<int> image_array = {69, 101, 128, 132, 109, 
                             136, 161, 165, 151, 169, 
                             210, 184, 166, 162, 245, 
                             242, 113, 32, 74, 18, 
                             228, 8, 33, 32, 15};
    
  for (int i = 0; i < size; ++i) {
    image_data[i] = static_cast<unsigned char>(i + 1);
    image_test[i] = static_cast<unsigned char>(image_array[i]);
  }

  // do the testing process
  Filter filter;
  Image image_res(width, height, channels, image_data, "test");
  Image image_result_box = filter.edge_detection(image_res, "scharr", "box_blur", 3, 0);

  unsigned char* image_box =image_result_box.getPixels();

  for(int i = 0; i<size; ++i){
    assert(image_box[i] == image_test[i]);
  }
  
  // Free memory allocated for the arrays
  delete[] image_test;
  
  std::cout << "The test passed for scharr edge detection!" << std::endl;

  return false;
}


// =======================================================================================
// Test Kernel functions
// =======================================================================================
bool Test::test_box_kernel(){
  int size = 5;
  Kernels kernel;
  vector<vector<double>> box_ker = kernel.box_kernel(5);

  vector<vector<double>> box_ker_test = {{0.04, 0.04, 0.04, 0.04, 0.04},
                                         {0.04, 0.04, 0.04, 0.04, 0.04},
                                         {0.04, 0.04, 0.04, 0.04, 0.04},
                                         {0.04, 0.04, 0.04, 0.04, 0.04},
                                         {0.04, 0.04, 0.04, 0.04, 0.04}};

    for(int i = 0; i<size; ++i){
      assert(box_ker[i] == box_ker_test[i]);
    }

    std::cout << "The test passed for box kernel function!" << std::endl;

    return true;
}

bool Test::test_gaussian_kernel(){
    int size = 5;
    Kernels kernel;
    vector<vector<double>> gau_ker = kernel.gaussian_kernel(5,1);

    vector<vector<double>> gau_ker_test = {{0.003, 0.013, 0.022, 0.013, 0.003},
                                           {0.013, 0.060, 0.098, 0.060, 0.013},
                                           {0.022, 0.098, 0.162, 0.098, 0.022},
                                           {0.013, 0.060, 0.098, 0.060, 0.013},
                                           {0.003, 0.013, 0.022, 0.013, 0.003}};

    double tolerance = 1e-3; // for comparison

    for(int i = 0; i<size; ++i){
      for(int j =0; j<size; ++j){
        assert(std::abs(gau_ker[i][j] - gau_ker_test[i][j]) < tolerance);
      }
    }
    
    std::cout << "The test passed for gaussian kernel function!" << std::endl;

    return true;
}

bool Test::test_sobel_kernel(){
  // generate the expected sobel kernel
  vector<vector<double>> sobel_x = {{1 , 0, -1},
                                    {2 , 0, -2},
                                    {1 , 0, -1}};
  vector<vector<double>> sobel_y = {{1 , 2, 1},
                                    {0 , 0, 0},
                                    {-1, -2, -1}};
  pair<vector<vector<double>>, vector<vector<double>>> sobel_test = make_pair(sobel_x, sobel_y);

  // generate the actual sobel kernel
  Kernels kernel;
  pair<vector<vector<double>>, vector<vector<double>>> sobel = kernel.sobel_kernel();

  // check size
  assert(sobel.first.size() == sobel_test.first.size());
  assert(sobel.second.size() == sobel_test.second.size());

  // check elements
  for (size_t i = 0; i < sobel.first.size(); ++i) {
    for (size_t j = 0; j < sobel.first[i].size(); ++j) {
      assert(sobel.first[i][j] == sobel_test.first[i][j]);
      assert(sobel.second[i][j] == sobel_test.second[i][j]);
    }
  }
  
  std::cout << "The test passed for sobel kernel function!" << std::endl;

  return true;
}

bool Test::test_prewitt_kernel(){
  // generate the expected sobel kernel
  vector<vector<double>> Prewitt_x = {{1 , 0, -1},
                                      {1 , 0, -1},
                                      {1 , 0, -1}};

  vector<vector<double>> Prewitt_y = {{1 , 1, 1},
                                      {0 , 0, 0},
                                      {-1, -1, -1}};
  pair<vector<vector<double>>, vector<vector<double>>> prewitt_test = make_pair(Prewitt_x, Prewitt_y);

  // generate the actual Prewitt kernel
  Kernels kernel;
  pair<vector<vector<double>>, vector<vector<double>>> prewitt = kernel.prewitt_kernel();

  // check size
  assert(prewitt.first.size() == prewitt_test.first.size());
  assert(prewitt.second.size() == prewitt_test.second.size());

  // check elements
  for (size_t i = 0; i < prewitt.first.size(); ++i) {
    for (size_t j = 0; j < prewitt.first[i].size(); ++j) {
      assert(prewitt.first[i][j] == prewitt_test.first[i][j]);
      assert(prewitt.second[i][j] == prewitt_test.second[i][j]);
    }
  }
  
  std::cout << "The test passed for prewitt kernel function!" << std::endl;

  return true;
}

bool Test::test_robert_cross_kernel(){
  // generate the expected sobel kernel
  vector<vector<double>> robert_cross_x = {{1, 0},
                                           {0, -1}};
    

  vector<vector<double>> robert_cross_y = {{0, 1},
                                           {-1, 0}};
  pair<vector<vector<double>>, vector<vector<double>>> robert_cross_test = make_pair(robert_cross_x, robert_cross_y);

  // generate the actual Prewitt kernel
  Kernels kernel;
  pair<vector<vector<double>>, vector<vector<double>>> robert_cross = kernel.robert_cross_kernel();

  // check size
  assert(robert_cross.first.size() == robert_cross_test.first.size());
  assert(robert_cross.second.size() == robert_cross_test.second.size());

  // check elements
  for (size_t i = 0; i < robert_cross.first.size(); ++i) {
    for (size_t j = 0; j < robert_cross.first[i].size(); ++j) {
      assert(robert_cross.first[i][j] == robert_cross_test.first[i][j]);
      assert(robert_cross.second[i][j] == robert_cross_test.second[i][j]);
    }
  }
  
  std::cout << "The test passed for robert cross kernel function!" << std::endl;

  return true;
}

bool Test::test_scharr_kernel(){
  // generate the expected sobel kernel
  vector<vector<double>> Scharr_x = {{3 , 0, -3},
                                     {10, 0, -10},
                                     {3 , 0, -3}};
    
  vector<vector<double>> Scharr_y = {{3 , 10, 3},
                                     {0 , 0, 0},
                                     {-3, -10, -3}};
  pair<vector<vector<double>>, vector<vector<double>>> Scharr_test = make_pair(Scharr_x, Scharr_y);

  // generate the actual Prewitt kernel
  Kernels kernel;
  pair<vector<vector<double>>, vector<vector<double>>> Scharr = kernel.scharr_kernel();

  // check size
  assert(Scharr.first.size() == Scharr_test.first.size());
  assert(Scharr.second.size() == Scharr_test.second.size());

  // check elements
  for (size_t i = 0; i < Scharr.first.size(); ++i) {
    for (size_t j = 0; j < Scharr.first[i].size(); ++j) {
      assert(Scharr.first[i][j] == Scharr_test.first[i][j]);
      assert(Scharr.second[i][j] == Scharr_test.second[i][j]);
    }
  }
  
  std::cout << "The test passed for scharr kernel function!" << std::endl;

  return true;
}


//===========================================================================================================
// Test for projection
//==========================================================================================================
bool Test::test_chosen_projection(const char* filename) {
    
    Volume volume(filename);
    volume.load();
    Projection project(volume);
    
    //creating images with each projection type
    //there are two images in the test_images folder, one black(i.e all pixels 0) and other white(i.e all pixels 255)
    Image max_image = project.chosen_projection("max", 1, 2); //max should give us a white picture i.e, all pixel values should be 255
    Image min_image = project.chosen_projection("min", 1, 2); //min should give us a black picture i.e, all pixel values should be 0  
    Image avg_image = project.chosen_projection("avg", 1, 2); //avg should give us a picture with all pixel values as (0+255)/2
                                                              // we will check these statements through assert statements in a for loop

    //validating dimensions of all images vs each other
    assert((max_image.getWidth() == min_image.getWidth())&& (min_image.getWidth() == avg_image.getWidth()));
    assert((max_image.getHeight() == min_image.getHeight()) && (min_image.getHeight() == avg_image.getHeight()));
    assert((max_image.getChannels() == min_image.getChannels()) && (min_image.getChannels() == avg_image.getChannels()));

    //calculating dimensions
    int w = min_image.getWidth();
    int h = min_image.getHeight();
    int c = min_image.getChannels();
    int pixel_idx;

    for (int j = 0; j < h; j++) {
        for (int i = 0; i < w; i++) {
            pixel_idx = (j * w + i) * c;
            //checking whether min returns black image, max returns white image and avg return grey image respectively
            assert(min_image.getPixels()[pixel_idx] == 0);
            assert(max_image.getPixels()[pixel_idx] == 255);
            assert(avg_image.getPixels()[pixel_idx] == ((255 + 0) / 2));
        }
    }
    
    //if the code reaches this line it means all assert statements have passed, hence return true
    std::cout << "All tests passed for chosen_projection()!" << std::endl;
    return true;
}


//===========================================================================================================
// Test for slice
//==========================================================================================================
bool Test::testSlice(const char *path)
{
    // Volume
    Volume volume(path);
    volume.load();

    // Slicer
    Slice slicer;
    int position = 100;
    const char *plane = "YZ";
    Image slicedImageYZ = slicer.slice(volume, plane, position);
    plane = "XZ";
    Image slicedImageXZ = slicer.slice(volume, plane, position);

    // Compare the results YZ
    assert(slicedImageYZ.getWidth() == volume.getHeight() &&
           "width is not equal");
    assert(slicedImageYZ.getHeight() ==
               volume.getTotalImages() * volume.getChannels() &&
           "height is not equal");
    assert(slicedImageYZ.getChannels() == volume.getChannels() &&
           "channels is not equal");

    // Compare the results XZ
    assert(slicedImageXZ.getWidth() == volume.getWidth() &&
           "width is not equal");
    assert(slicedImageXZ.getHeight() ==
               volume.getTotalImages() * volume.getChannels() &&
           "height is not equal");
    assert(slicedImageXZ.getChannels() == volume.getChannels() &&
           "channels is not equal");

    std::cout << "All tests passed for slice()!" << std::endl;
    return true;
};