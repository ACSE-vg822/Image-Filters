// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

# include "./../include/projection.h"

// to ensure that image.cpp is not included twice, I am including filter.cpp
// image.cpp is required to create image object

// Contructor
Projection::Projection(Volume &volume)
{
	this->data = volume.getData();			  // pixel data of all images
	this->w = volume.getWidth();			  // width of indiviudal images
	this->h = volume.getHeight();			  // height of indiviudal images
	this->c = volume.getChannels();			  // no. of channels in indiviudal images
	this->n_images = volume.getTotalImages(); // no. of images in the volume
	std::cout << "No. of images in the volume: " << this->n_images << std::endl;
	// this->projected = nullptr;
	std::cout << "Data loaded into projection class!" << std::endl;
};

/*
-----------------------
||	PRIVATE METHOD    ||
-----------------------
*/
// method to allocate memory for producing projected image
void Projection::allocate(int size)
{
	this->projected = new unsigned char[size]; // Create an empty data for the projected image
}

/*-----------------------
|| PUBLIC METHOD       ||
-----------------------*/
// methods to output the chosen projection
Image Projection::chosen_projection(std::string choice, int start_img, int end_img)
{
	std::cout << this->c << std::endl;
	// Takes a projection type as input parameter and performs that projection
	/*int choice :
	choice = min -> Minmimum Intensity
	choice = max -> Maximum Intensity
	choice = avg -> Average Intensity
	
	int start_img, int end_img:
	according to user input, projection is created for a slice of volume starting from
	start_img and ending at end_img*/

	this->allocate(this->w * this->h * this->c); // creating memory space for output image

	// pixel index in the 1D array of volume and image respectively
	//vol_idx used to traverse 3D volume, img_idx used to traverse allocated memory for 2D projection image
	int vol_idx, img_idx; 

	// initialzing the projected image with first image

	// if the images have 1 or 2 channel(s)
	if (this->c <= 2)
	{
		for (int j = 0; j < this->h; j++)
		{
			for (int i = 0; i < this->w; i++)
			{
				img_idx = (j * this->w + i) * this->c;
				vol_idx = (j * this->w + i) * this->c * this->n_images;
				this->projected[img_idx + 0] = this->data[vol_idx + 0];
			}
		}
		
		//if alpha channel exists then simply copy over the values to the 2D projection 
		if (this->c % 2 == 0)
		{
			this->projected[img_idx + 1] = this->data[vol_idx + 1];
		}
	}

	// if the images have 3 or 4 channels
	if (this->c > 2)
	{
		for (int j = 0; j < this->h; j++)
		{
			for (int i = 0; i < this->w; i++)
			{
				img_idx = (j * this->w + i) * this->c;
				vol_idx = (j * this->w + i) * this->c * this->n_images;
				this->projected[img_idx + 0] = this->data[vol_idx + 0];
				this->projected[img_idx + 1] = this->data[vol_idx + 1];
				this->projected[img_idx + 2] = this->data[vol_idx + 2];
			}
		}

		//if alpha channel exists then simply copy over the values to the 2D projection 
		if (this->c % 2 == 0)
		{
			this->projected[img_idx + 3] = this->data[vol_idx + 3];
		}
	}

	std::vector<double> temp_sum(this->w * this->h * this->c, 0); // to store the temporary sum for each pixel
	
	// traversing over each image
	for (int img = start_img; img < end_img; img++)
	{
		for (int j = 0; j < this->h; j++)
		{
			for (int i = 0; i < this->w; i++)
			{
				img_idx = (j * this->w + i) * this->c;
				vol_idx = (j * this->w + i) * this->c * this->n_images + img * this->c;

				// if the images have 1 or 2 channel(s)
				if (this->c <= 2)
				{

					if (choice == "min")
					{ // Minimum Intensity
						//Choose the pixel with minimum intensity and copy to projected data
						this->projected[img_idx] = std::min(this->projected[img_idx], this->data[vol_idx]);
					}
					if (choice == "max")
					{ // Maximum Intensity
						//Choose the pixel with maximum intensity and copy to projected data
						this->projected[img_idx] = std::max(this->projected[img_idx], this->data[vol_idx]);
					}
					if (choice == "avg")
					{ // Average Intensity
						//first, sum all the pixel intensities
						temp_sum[img_idx] += this->data[vol_idx];

						//then, upon reaching last image, divide the sum by no. of images to
						//then save this mean to projected data
						if (img == this->n_images - 1)
						{
							this->projected[img_idx] = static_cast<unsigned char>(temp_sum[img_idx] / static_cast<float>(this->n_images));
						}
					}
					//if alpha channel exists then simply copy over the values to the 2D projection 
					if (this->c % 2 == 0)
					{
						this->projected[img_idx + 1] = this->data[vol_idx + 1];
					}
				}

				// if the images have 3 or 4 channels
				if (this->c > 2)
				{

					if (choice == "min")
					{ // Minimum Intensity
						//Choose the pixel with minimum intensity and copy to projected data
						this->projected[img_idx + 0] = std::min(this->projected[img_idx + 0], this->data[vol_idx + 0]);
						this->projected[img_idx + 1] = std::min(this->projected[img_idx + 1], this->data[vol_idx + 1]);
						this->projected[img_idx + 2] = std::min(this->projected[img_idx + 2], this->data[vol_idx + 2]);
					}
					if (choice == "max")
					{ // Maximum Intensity
						//Choose the pixel with maximum intensity and copy to projected data
						this->projected[img_idx + 0] = std::max(this->projected[img_idx + 0], this->data[vol_idx + 0]);
						this->projected[img_idx + 1] = std::max(this->projected[img_idx + 1], this->data[vol_idx + 1]);
						this->projected[img_idx + 2] = std::max(this->projected[img_idx + 2], this->data[vol_idx + 2]);
					}
					if (choice == "avg")
					{ // Average Intensity
						//first, sum all the pixel intensities
						temp_sum[img_idx + 0] += this->data[vol_idx + 0];
						temp_sum[img_idx + 1] += this->data[vol_idx + 1];
						temp_sum[img_idx + 2] += this->data[vol_idx + 2];

						//then, upon reaching last image, divide the sum by no. of images to
						//then save this mean to projected data
						if (img == this->n_images - 1)
						{
							this->projected[img_idx + 0] = static_cast<unsigned char>(temp_sum[img_idx + 0] / static_cast<float>(this->n_images));
							this->projected[img_idx + 1] = static_cast<unsigned char>(temp_sum[img_idx + 1] / static_cast<float>(this->n_images));
							this->projected[img_idx + 2] = static_cast<unsigned char>(temp_sum[img_idx + 2] / static_cast<float>(this->n_images));
						}
					}
					//if alpha channel exists then simply copy over the values to the 2D projection 
					if (this->c % 2 == 0)
					{
						this->projected[img_idx + 3] = this->data[vol_idx + 3];
					}
				}
			}
		}
	}
	std::string res_filename = "projection.png";
	int w = this->w;
	int h = this->h;
	int c = this->c;
	return Image(w, h, c, this->projected, res_filename);
}