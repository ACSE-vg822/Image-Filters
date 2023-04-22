// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <sstream>
#include <string>

#include "./../include/image.h"

#include "./../include/stb_image.h"
#include "./../include/stb_image_write.h"

// Note :
//      1. Must use c++17 in order to use <filesystem>
//      ref: https://stackoverflow.com/questions/59127732/how-to-enable-c17-on-vscodemac

// -------------------------
//      Constructors
// -------------------------

Image::Image(){};

Image::Image(const char *fname) : filename(fname){this->save_name = "original.png";};

Image::Image(Image &other)
{
    // Clear previously allocated data, creating an empty image
    this->w = other.getWidth();
    this->h = other.getHeight();
    this->c = other.getChannels();
    int size = other.getWidth() * other.getHeight() * other.getChannels();
    this->data = new unsigned char[size];
    for (int i = 0; i < size; ++i)
    {
        this->data[i] = other.data[i];
    }
    this->save_name = "original.png";
};

Image::Image(int &w, int &h, int &c, unsigned char *data, std::string saving_name)
{
    this->w = w;
    this->h = h;
    this->c = c;
    this->data = data;
    this->filename = " ";
    this->save_name = saving_name;

    unsigned char value = 0;
    int counter = 0;
    for (int i = 0; i < w * h * c; i++)
    {
        value = data[i];
        counter++;
    }
    std::cout << "w x h x c = " << w * h * c << " | Size = " << counter << std::endl;
};

Image::~Image()
{
    if (this->data != NULL)
        stbi_image_free(this->data);
    std::cerr << "Image Destructor" << std::endl;
}

// -------------------------
//      Public methods
// -------------------------
void Image::info()
{
    bool ok = stbi_info(this->filename, &this->w, &this->h, &this->c);
}

int Image::load()
{
    // Load the data using STBI library
    this->data = stbi_load(this->filename,
                           &this->w,
                           &this->h,
                           &this->c,
                           0);

    // Error message
    if (this->data == NULL)
    {
        std::cout << "Error in loading the image" << std::endl;
        return 0;
    }
    else
        return 1;
};

int Image::save(std::string output_path)
{
    // Save the image using STBI library
    int success = stbi_write_png(output_path.c_str(), this->w,
                                 this->h, this->c,
                                 this->data, 0);
    return success;
};

std::string Image::get_name_in_path(std::string file_path)
{
    std::stringstream ss(file_path);            // Construct a string stream
    std::string word = file_path;                       // Construct a string for getline to write
    while (std::getline(ss, word, '/')) word;

    std::string filename;       
    std::stringstream ss2(word);  
    while (std::getline(ss2, filename, '.')) {filename; break;}
    return filename;

};