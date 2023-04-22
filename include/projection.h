// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

// header file for projection class
#ifndef PROJECTION
#define PROJECTION


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

# include "image.h"
# include "volume.h"

/*
Projection class provides functionality to obtain 2D projections for 3D image volume,
composed of 2D images. Based on user input, the method chosen_projection will produce
projection composed of either maximum intensity of all images or minimum intensity or
average intensity of all pixels.

A Projection object can be initialized by passing a volume object:

	Projection(volume);

The description of the methods available to users is below.
// Written by Vidushee Geetam (2023)
*/
#include <string>
class Projection
{

public:
	// Constructor
	// Parameters: volume is an object of class Volume
	Projection(Volume &volume);

	// Destructor
	~Projection(){};

	// Method(s)
	// Takes a projection type as input parameter and performs that projection
	/*int choice :
	choice = 1 -> Minmimum Intensity
	choice = 2 -> Maximum Intensity
	choice = 3 -> Average Intensity*/
	Image chosen_projection(std::string, int, int);

private:
	// variables to store the volume width, height, no of channels and total number of images
	int w, h, c, n_images;
	unsigned char *projected;
	unsigned char *data;
	std::string folder_name;
	// function to allocate memory for producing projected image
	void allocate(int size);
};
#endif
