# Advanced Programming Group Project

## Linear-Regression Group

This repository contains the code submitted for assessment for Linear-Regression Group's C++ Group Project. It is a C++ program which applies a range of image filters and orthographic projections to an input 2D image or 3D data volume. The program contains a main function which reads an image or data volume, asks the user which filter or projection to apply, calls separate functions for the appropriate filter and/or projections, and saves the new image with the filter/projection applied. The program could work with any arbitrary image/data volume size.

## C++ complier
The C++ version and the version should be C++17 at least.

## Instructions

Run `main.cpp` file, then following the prompts to enter the name of the image. Choosing the different filter to process the image. The reuslt will store in `output` 
folder. Ensure there's a folder called "Scans" in parent directory containing the correct 3D image volumes.

The commend is shown below:  
  
```g++-12 -o user_interface user_interface.cpp kernels.cpp conv_tool.cpp image.cpp volume.cpp filter.cpp projection.cpp slice.cpp```

if you want run all the result you have to use the commond below:  
  
```g++-12 -o main main.cpp kernels.cpp conv_tool.cpp image.cpp volume.cpp filter.cpp projection.cpp slice.cpp```

Hint: Users can only enter one image at a time using the program. 

## Execution
main - MacOS executable for main.cpp, 
windows_main_exe - Windows executable for main.cpp, 
user_interface - MacOS executable for user_interface.cpp, 
windows_interface_exe - Windows executable for user_interface.cpp

## Document
Detailed descriptions of all filters are presented in the report for aggregation

## Example Output
![image](https://user-images.githubusercontent.com/110220811/227563409-6c6f7649-07f5-40c1-81a5-afc0d9979300.png)

The image show the ouput picture by applying the sobel and gaussian blur for edge detection.

The following link is the data volume after blurring:
https://drive.google.com/file/d/19VB5SM6FYKk5vbDYsoN7GThcU8t3UN-w/view?usp=sharing

## More information
For more information ont the project specfication or the output, please see the PDF `AdvProg_ProjectDescription.pdf` and `output` floder.

All user should create the new folder by themselves for saving there output before using the programme
