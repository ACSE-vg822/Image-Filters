// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#include "./../include/volume.h"

#include <fstream>
#include <cstdlib>
#include <filesystem>
#include <vector>
#include <sstream>
#include <cstring>
#include <string>

#include "./../include/stb_image.h"
#include "./../include/stb_image_write.h"

// to get it working on windows, not required on mac when compiling with g++12
// #include <filesystem>

// -------------------------
//      Constructors
// -------------------------

Volume::Volume(const char *path) : path(path) { this->getImageFiles(); };

Volume::Volume(int &w, int &h, int &c,
          unsigned char *data, std::vector<std::string> input_filenames) {

    this->width = w;
    this->height= h;
    this->images= input_filenames;
    this->data = data;

    unsigned char value = 0;
    int counter = 0;
    for (int i = 0; i < w * h * c; i++)
    {
        value = data[i];
        counter++;
    }
    std::cout << "w x h x c = " << w * h * c << " | Size = " << counter << std::endl;
};

Volume::~Volume()
{
    delete[] this->data;
    std::cout << "Volume Destructor" << std::endl;
};

// -------------------------
//      Public methods
// -------------------------

int Volume::getWidth() { return this->width; };

int Volume::getHeight() { return this->height; };

int Volume::getChannels() { return this->channel; };

int Volume::getTotalImages() { return this->images.size(); };

unsigned char *Volume::getData() { return this->data; };

std::vector<std::string> Volume::getFileNames(){return this->images;};

void Volume::info()
{
    // Write a single image properties to volume class parameters
    char *filename = generateSingleImagePath();
    bool ok = stbi_info(filename, &this->width, &this->height, &this->channel);

    // Memory management
    delete[] filename;
}

void Volume::load()
{
    // Generate the image properties
    this->info();

    // Allocate memory for the volume pixels to store
    // all the 2D images, each one as one channel
    int volumeChannel = this->images.size() * this->channel;
    this->allocate(volumeChannel);

    // Load each image individually in a temporary memory space
    // and stores it accordingly to the 1D representation.
    unsigned char *tmp;
    for (int c = 0; c < this->images.size(); c++){
        
        // Read a single image from this->images
        char *filename = generateSingleImagePath(c);
        tmp = stbi_load(filename,
                        &this->width,
                        &this->height,
                        &this->channel,
                        0);

        // Store the single image pixels in its position in the
        // final volume data according to the 1D array format of stbi
        for (int i = 0; i < this->height; i++)
        {
            for (int j = 0; j < this->width; j++)
            {

                int index = (i * this->width + j) * this->channel;                        // Image indexing (1D)
                int indexOut = (i * this->width + j) * volumeChannel + c * this->channel; // Volume indexing (3D)

                // Create the volume with grey images and rbg images
                if (this->channel <= 2)
                {
                    this->data[indexOut + 0] = tmp[index + 0];
                    if (this->channel % 2 == 0)
                    { // checking if alpha exists
                        this->data[indexOut + 1] = tmp[index + 1];
                    }
                }
                else if (this->channel > 2)
                {
                    this->data[indexOut + 0] = tmp[index + 0];
                    this->data[indexOut + 1] = tmp[index + 1];
                    this->data[indexOut + 2] = tmp[index + 2];
                    if (this->channel % 2 == 0)
                    { // checking if alpha exists
                        this->data[indexOut + 3] = tmp[index + 3];
                    }
                }
            }
        }

        // Memory management
        stbi_image_free(tmp);
    }
};

int Volume::save(std::string output_path) {
    std::vector<std::string> output_file_paths = this->get_output_file_paths(output_path);
    int success = 0;
    int volumeChannel = this->images.size() * this->channel;
    
    for (int i = 0; i < images.size(); ++i) {
        // generate one image 
        unsigned char* one_image = new unsigned char[this->width * this->height * this->channel];

        for (int h = 0; h < this->height; h++) {
            for (int w = 0; w < this->width; w++) {
                int volumeIndex = (h * this->width + w) * volumeChannel + i * this->channel;
                int imageIndex = (h * this->width + w) * this->channel;

                for (int c = 0; c < this->channel; c++) {
                    one_image[imageIndex + c] = this->data[volumeIndex + c];
                }
            }
        }

        success += stbi_write_png(output_file_paths[i].c_str(), this->width,
                                  this->height, this->channel,
                                  one_image, 0);
        delete[] one_image;
    }
    return (success - images.size() + 1);
};

std::vector<std::string> Volume::get_output_file_paths(std::string output_path) {
    std::vector<std::string> result;
    for (int i=0; i<images.size(); ++i) {
        std::stringstream ss(this->images[i]);            // Construct a string stream
        std::string word;                         // Construct a string for getline to write
        while (std::getline(ss, word, '/')) word;
        result.push_back((output_path + "/" + word));
    }
    return result;
};

// -------------------------
//      Private methods
// -------------------------
void Volume::getImageFiles()
{
    for (const auto &entry : std::filesystem::directory_iterator(this->path))
    {
        std::vector<std::string> output;                   // Creates the vector of strings
        tokenize(entry.path(), output);                    // Split the path into strings
        this->images.push_back(output[output.size() - 1]); // Append the image file to the list
    }
    this->sortImageFiles(); // Sort the image files listed
};

void Volume::tokenize(std::string const &string,
                      std::vector<std::string> &output,
                      const char delimiter)
{
    std::stringstream ss(string);            // Construct a string stream
    std::string str;                         // Construct a string for getline to write
    while (std::getline(ss, str, delimiter)) // Write to string and push to the output
        output.push_back(str);
};

void Volume::sortImageFiles() { 
    int n = this->images.size();

    // Perform bubble sort on the vector of strings
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (this->images[j] > this->images[j + 1]) {
                // Swap the elements at indices j and j+1
                std::string temp = this->images[j];
                this->images[j] = this->images[j + 1];
                this->images[j + 1] = temp;
            }
        }
    }
 };

void Volume::allocate(int channels)
{
    int size = (this->width) * (this->height) * channels; // Define the size of the image data
    this->data = new unsigned char[size];                 // Create an empty data for the filtered image
};

char *Volume::generateSingleImagePath(int index)
{
    const char *delimiter = "/";
    char *filename = new char[strlen(this->path) +
                              strlen(delimiter) +
                              strlen(this->images[index].c_str()) +
                              1];
    std::strcpy(filename, this->path);
    std::strcat(filename, delimiter);
    std::strcat(filename, this->images[index].c_str());
    return filename;
};
