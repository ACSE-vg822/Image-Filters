// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#ifndef IMAGE
#define IMAGE

# include <vector>
# include <string>
#include <iostream>


class Image
{
public:
    // Constructor
    Image();
    Image(const char *fname);

    // Copy constructor works as a memory allocator
    // by creating a new Image with no data stored
    Image(Image &other);

    // Constructor
    Image(int &w, int &h, int &c,
          unsigned char *data, std::string saving_name);

    // Destructor
    ~Image();

    // Getters
    int getWidth() { return this->w; };
    int getHeight() { return this->h; };
    int getChannels() { return this->c; };
    bool existsAlpha() { return ((this->c % 2) == 0); };
    unsigned char *getPixels() { return this->data; };
    const char* getFilename() { return filename; };

    // Methods
    void info();
    int load();
    int save(std::string output_path);
    std::string get_name_in_path(std::string file_path);
    std::string save_name;

private:
    int w, h, c, success;
    unsigned char *data;
    const char *filename;
};

#endif