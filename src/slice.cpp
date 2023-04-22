// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#include <iostream>
#include <cstdlib>
#include <cstring>

#include "./../include/slice.h"
#include <cassert>

// -------------------------
//      Constructors
// -------------------------
Slice::Slice() {};

Slice::~Slice() {};

// -------------------------
//      Public methods
// -------------------------
Image Slice::slice(Volume& volume, const char* plane, int& position)
{
    // Get the volume dimensions
    int width = volume.getWidth();
    int height = volume.getHeight();
    int imageChannels = volume.getChannels();
    int images = volume.getTotalImages();
    int volumeChannels = images * imageChannels;

    // Check if user input is valid
    if (std::strcmp(plane, "XZ") == 0)
        assert(position < height && "position is out of bounds");
    else if (std::strcmp(plane, "YZ") == 0)
        assert(position < width && "position is out of bounds");

    // Get the volume data
    unsigned char* data = volume.getData();

    // Declare a variable to store the sliced data
    unsigned char* slicedData;

    int sliceHeight, sliceWidth, sliceChannels;

    // Perform the slicing operation for the specified plane
    if (std::strcmp(plane, "XZ") == 0)
    {
        sliceHeight = images;
        sliceWidth = width;
        sliceChannels = imageChannels;

        slicedData = new unsigned char[sliceHeight * sliceWidth * sliceChannels];
        
        for (int z = 0; z < sliceHeight; z++)
        {   //std::cout << "flagz"<<z<<std::endl;
            for (int x = 0; x < sliceWidth; x++)
            {
                //std::cout << "flagx" << std::endl;
                int volumeIndex = (position * width + x) * volumeChannels + z * imageChannels;
                int sliceIndex = (z * sliceWidth + x) * sliceChannels;

                for (int c = 0; c < sliceChannels; c++)
                {
                    slicedData[sliceIndex + c] = data[volumeIndex + c];
                    // std::cout << "flagc"<<(z+1)*(x+1)*(c+1)<<std::endl;
                    // std::cout << "size: " << sliceHeight * sliceWidth * sliceChannels << std::endl;
                }
            }
        }
    }
    else if (std::strcmp(plane, "YZ") == 0)
    {
        sliceHeight = images;
        sliceWidth = height;
        sliceChannels = imageChannels;

        slicedData = new unsigned char[sliceHeight * sliceWidth * sliceChannels];

        for (int z = 0; z < sliceHeight; z++)
        {
            for (int y = 0; y < sliceWidth; y++)
            {
                int volumeIndex = (y * width + position) * volumeChannels + z * imageChannels;
                int sliceIndex = (z * sliceWidth + y) * sliceChannels;

                for (int c = 0; c < sliceChannels; c++)
                {
                    slicedData[sliceIndex + c] = data[volumeIndex + c];
                }
            }
        }
    }
    else
    {
        throw std::invalid_argument("Invalid plane specified. Only XZ and YZ planes are supported.");
    }
    //Image slicedImage(slicedData, width, height, imageChannels);
    std::string res_filename = "slice.png";
    return Image(sliceWidth, sliceHeight, sliceChannels, slicedData, res_filename);
};
