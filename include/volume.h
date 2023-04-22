// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#ifndef VOLUME
#define VOLUME

#include <iostream>
#include <vector>


// #include "image.h"
// #include <filesystem>

// The volume class provides functionality to manipulate three-dimensional
// images composed of two-dimensional image composition, in which each one
// corresponds to a channel in the 3D image.
//
// The initialization of a Volume object is given from a path to the set of
// 2D images, i.e.:
//
//      const char *path = "../scans/confuciusornis";
//      Volume volume(path);
//
// The description of the methods available to users is below.
// Written by G. Machado (2023)

class Volume
{
public:
    // Constructor
    // Parameters:
    //     const char *path : path to the folder containing the 2D images
    explicit Volume(const char *path);

    Volume(int &w, int &h, int &c,
          unsigned char *data, std::vector<std::string> input_filenames);

    // Destructor
    ~Volume();

    // Getters: functions to return the width, height,
    // depth(total number of 2-D images) and no. of channels of
    // the volume:
    int getWidth();           // Width of a single image
    int getHeight();          // Height of a single image
    int getTotalImages();     // Total number of images in a volume
    int getChannels();        // Number of channels of a single image
    unsigned char *getData(); // Pixel data of the volume
    std::vector<std::string> getFileNames();

    // Obtain the dimensions for a single image, writing those properties
    // to w, h and c parameters of the volume class
    void info();

    // Construct the volume data parameter based on the 2D images
    // found in the path given
    void load();

    // save vol
    int save(std::string output_path);

    std::vector<std::string> get_output_file_paths(std::string output_path);

protected:
    const char *path;                // Folder path
    std::vector<std::string> images; // List of all the image files inside the folder
    int width, height, channel;      // Dimensions of each image in a volume
    unsigned char *data = nullptr;             // Volume pixels

    

private:
    // Get the list of all image files in the given path and
    // store in the images parameter as a vector of strings
    void getImageFiles();

    // Splits a file path based on the delimiter, which is
    // defined as '/', and write each substring into a
    // std::vector<std::string> given by output
    void tokenize(std::string const &string,
                  std::vector<std::string> &output,
                  const char delimiter = '/');

    // Sort the vector of image files based on its name,
    // assuming the numbering represents the ordering of
    // the images in a 3D image. i.e:
    // confuYZ0001.png, confuYZ0002.png, ... , confuYZ0256.png
    void sortImageFiles();

    // Allocate memory for the 3D volume data parameter based
    // on the image properties contained in the given path folder
    void allocate(int channels);

    // Creat the C-string containing the image path for a
    // given image defined by its index on the images properties
    char *generateSingleImagePath(int index = 0);
};
#endif 
