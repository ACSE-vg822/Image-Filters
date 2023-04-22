// Linear-Regression:
// Yulin Zhuo: edsml-yz6622
// Yifan Wang: edsml-yw3022
// Chenyu Ren: acse-cr22
// Vidushee Geetam: acse-vg822
// Gustavo Machado: acse-gpm22

#include <iostream>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "./../include/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "./../include/stb_image_write.h"

# include "./../include/image.h"
# include "./../include/volume.h"
# include "./../include/filter.h"
# include "./../include/projection.h"
# include "./../include/slice.h"
# include <iostream>

void print_category_menu() {
    std::cout << "Choose which categories you want to use:" << '\n';
    std::cout << "1. Colour correction" << '\n';
    std::cout << "2. Image blur" << '\n';
    std::cout << "3. Edge detection" << '\n';
}
void print_color_menu() {
    std::cout << "Choose one of the color balance filters to apply:" << '\n';
    std::cout << "1. Greyscale" << '\n';
    std::cout << "2. Auto Color Balance" << '\n';
    std::cout << "3. Brightness Adjustment" << '\n';
    std::cout << "4. Histogram Equalisation Filter" << '\n';
}

void print_blur_menu() {
    std::cout << "Choose one of the blur filters to apply:" << '\n';
    std::cout << "1. Gaussian Blur" << '\n';
    std::cout << "2. Box Blur" << '\n';
    std::cout << "3. Median Blur" << '\n';
}

void print_edge_menu() {
    std::cout << "Choose one of the edge detection filters to apply:" << '\n';
    std::cout << "1. Sobel Edge Detection" << '\n';
    std::cout << "2. Prewitt Edge Detection" << '\n';
    std::cout << "3. Scharr Edge Detection" << '\n';
    std::cout << "4. Roberts' Cross Edge Detection" << '\n';
}

void apply_colour(Filter& filter, Image& image, int user_choice, Image& output_image){
    // Apply the colour correction filter
    if (user_choice == 1){
        output_image = filter.greyScale(image);
    }
    else if (user_choice == 2){
        output_image = filter.autoColorBalance(image);
    }
    else if (user_choice == 3){
        output_image = filter.brightness(image,100,false);
    }
    else if (user_choice == 4){
        output_image = filter.histogramEqualization(image);
    }
}

void apply_blur(Filter& filter, Image& image, int user_choice, Image& output_image){
    // Apply the blur filter
    if (user_choice == 1){
        output_image = filter.blur(image, "gaussian_blur", 3, 0.04);
    }
    else if (user_choice == 2){
        output_image = filter.blur(image, "box_blur", 3, 0);
    }
    else if (user_choice == 3){
        output_image = filter.blur(image, "median_blur", 3, 0);
    }
}

void apply_edge(Filter& filter, Image& image, int user_choice, Image& output_image){
    // Apply edge detection filter
    if (user_choice == 1){
        output_image = filter.edge_detection(image, "sobel", "box", 3, 0);
    }
    else if (user_choice == 2){
        output_image = filter.edge_detection(image, "prewitt", "box", 3, 0);
    }
    else if (user_choice == 3){
        output_image = filter.edge_detection(image, "scharr", "box", 3, 0);
    }
    else if (user_choice == 4){
        output_image = filter.edge_detection(image, "robert_cross", "box", 3, 0);
    }
}

// apply multiple filters
void apply_filter_multiply(char choice, Filter& filter, Image& image, int user_choice, Image& output_image){
    while(choice == 'y'){
        print_category_menu();
        std::cin>>user_choice;
        if(user_choice == 1){
            print_color_menu();
            std::cin>>user_choice;
            apply_colour(filter, image, user_choice, output_image);
        }
        else if(user_choice == 2){
            print_blur_menu();
            std::cin>>user_choice;
            apply_blur(filter, image, user_choice, output_image);
        }
        else if(user_choice == 3){
            print_edge_menu();
            std::cin>>user_choice;
            apply_edge(filter, image, user_choice, output_image);
        }

        std::cout << "Do you want to use another filter? (y/n): ";
        std::cin >> choice;
    }
}

void check_user_choice(int max_choice, int user_choice) {
    while (user_choice < 1 || user_choice > max_choice) {
        std::cout << "Invalid choice. Please enter a number between 1 and 4: ";
        std::cin >> user_choice;
    }
}

int main() {
    int user_choice;

    // Display a message
    std::cout << "You can now do the imgae processing." << std::endl ;

    // input file names
    std::string input_filename;
    std::cout << "Enter the input image file name: ";
    std::cin >> input_filename;
    
    // Load from Images folder
    std::string full_input_path = "../Images/" + input_filename + ".png";
    // const char *filename = "../Images/stinkbug.png";
    Image image(full_input_path.c_str());
    int status = image.load();
    std::cout << "Loading: " << status << std::endl;

    // Show the available image processing categories
    print_category_menu();

    // Enter the user choice
    std::cout << "Enter your choice (1-3): ";
    std::cin >> user_choice;

    // Check for valid input
    check_user_choice(3, user_choice);

    // filtr object
    Filter filter;
    // output image
    Image f_image;
    // Apply the filter
    if (user_choice == 1){
        // Show the available filters
        print_color_menu();
        // Enter the user choice
        std::cout << "Enter your choice (1-4): ";
        std::cin >> user_choice;
        // Check for valid input
        check_user_choice(4, user_choice);
        // Apply the filter
        apply_colour(filter, image, user_choice, f_image);
    }
    else if(user_choice == 2){
        // Show the available filters
        print_blur_menu();
        // Enter the user choice
        std::cout << "Enter your choice (1-3): ";
        std::cin >> user_choice;
        // Check for valid input
        check_user_choice(3, user_choice);
        // Apply the filter
        apply_blur(filter, image, user_choice, f_image);
    }
    else if(user_choice == 3){
        // Show the available filters
        print_edge_menu();
        // Enter the user choice
        std::cout << "Enter your choice (1-4): ";
        std::cin >> user_choice;
        // Check for valid input
        check_user_choice(4, user_choice);
        // Apply the filter
        apply_edge(filter, image, user_choice, f_image);
    }

    std::cout<<"Do you want to use another filter? (y/n): ";
    char choice;
    std::cin>>choice;
    if(choice == 'y'){
        apply_filter_multiply(choice, filter, image, user_choice, f_image);
    }
    
    // Save the image
    status = f_image.save("./../Output/" + input_filename + ".png");
    std::cout << "The output image saved to " << "./../Output/" << input_filename << ".png" << std::endl;
    
    return 0;
}
