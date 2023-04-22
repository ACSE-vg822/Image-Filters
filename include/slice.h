// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#ifndef SLICE
#define SLICE

#include "image.h"
#include "volume.h"

class Slice
{
public:
    // Constructor
    Slice();

    // Destructor
    ~Slice();

    Image slice(Volume &volume,
                const char *plane,
                int &position);
};
#endif
