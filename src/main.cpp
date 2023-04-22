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
#include <chrono>

//=====================================================================================================================
//MENTION: Recommended to generate each image one by one to avoid memory related problem.
//=====================================================================================================================

int main()
{
    auto start = chrono::high_resolution_clock::now(); /// Start timer for vector insertion
    Filter filter;
    
    //scans/confuciusornis slice xz-420
    const char *path_con = "../Scans/confuciusornis";

    Volume volume(path_con);
    volume.load();
    Slice slicer;
    const char *plane = "XZ";
    int position = 420;
    Image slicedImage = slicer.slice(volume, plane, position);
    std::string p_str(plane);
    std::string pure_name = slicedImage.get_name_in_path(slicedImage.save_name);
    slicedImage.save("./../Output/confuciusornis/" + pure_name + "_" + p_str + ".png");
    // /scans/confuciusornis slice yz-400
    Volume volume1(path_con);
    volume1.load();
    Slice slicer1;
    const char *plane1 = "YZ";
    int position1 = 400;
    Image slicedImage1 = slicer1.slice(volume1, plane1, position1);
    std::string p_str1(plane1);
    std::string pure_name1 = slicedImage1.get_name_in_path(slicedImage1.save_name);
    slicedImage1.save("./../Output/confuciusornis/" + pure_name1 + "_" + p_str1 + ".png");

    // /scans/fracture slice xz-138
    const char *path_frac = "../Scans/fracture";

    Volume volume2(path_frac);
    volume2.load();
    Slice slicer2;
    const char *plane2 = "XZ";
    int position2 = 138;
    Image slicedImage2 = slicer2.slice(volume2, plane2, position2);
    std::string p_str2(plane2);
    std::string pure_name2 = slicedImage2.get_name_in_path(slicedImage2.save_name);
    slicedImage2.save("./../Output/fracture/" + pure_name2 + "_" + p_str2 + ".png");
    // /scans/fracture slice yz-275
    Volume volume3(path_frac);
    volume3.load();
    Slice slicer3;
    const char *plane3 = "YZ";
    int position3 = 275;
    Image slicedImage3 = slicer3.slice(volume3, plane3, position3);
    std::string p_str3(plane3);
    std::string pure_name3 = slicedImage3.get_name_in_path(slicedImage3.save_name);
    slicedImage3.save("./../Output/fracture/" + pure_name3 + "_" + p_str3 + ".png");    

    //scans/confuciusornis projection max
    Volume volume4(path_con);
    volume4.load();
    Projection project4(volume4);
    const char *model4="max"; //avg, min
    std::string model_str4(model4);
    Image projected_image4 = project4.chosen_projection("max", 1, 265);
    std::string pure_name4 = projected_image4.get_name_in_path(projected_image4.save_name);
    projected_image4.save("./../Output/confuciusornis/" + pure_name4 + "_" + model_str4 + "_all.png");

    // /scans/confuciusornis projection min
    Volume volume5(path_con);
    volume5.load();
    Projection project5(volume5);
    const char *model5="min"; //avg, min
    std::string model_str5(model5);
    Image projected_image5 = project5.chosen_projection("min", 1, 265);
    std::string pure_name5 = projected_image5.get_name_in_path(projected_image5.save_name);
    projected_image5.save("./../Output/confuciusornis/" + pure_name5 + "_" + model_str5 + "_all.png");

    // /scans/confuciusornis projection avg
    Volume volume6(path_con);
    volume6.load();
    Projection project6(volume6);
    const char *model6="avg"; //avg, min
    std::string model_str6(model6);
    Image projected_image6 = project6.chosen_projection("avg", 1, 265);
    std::string pure_name6 = projected_image6.get_name_in_path(projected_image6.save_name);
    projected_image6.save("./../Output/confuciusornis/" + pure_name6 + "_" + model_str6 + "_all.png");

    // /scans/fracture projection max
    Volume volume7(path_frac);
    volume7.load();
    Projection project7(volume7);
    const char *model7="max"; //avg, min
    std::string model_str7(model7);
    Image projected_image7 = project7.chosen_projection("max", 1, 1300);
    std::string pure_name7 = projected_image7.get_name_in_path(projected_image7.save_name);
    projected_image7.save("./../Output/fracture/" + pure_name7 + "_" + model_str7 + "_all.png");

    // /scans/fracture projection min
    Volume volume8(path_frac);
    volume8.load();
    Projection project8(volume8);
    const char *model8="min"; //avg, min
    std::string model_str8(model8);
    Image projected_image8 = project8.chosen_projection("min", 1, 1300);
    std::string pure_name8 = projected_image8.get_name_in_path(projected_image8.save_name);
    projected_image8.save("./../Output/fracture/" + pure_name8 + "_" + model_str8 + "_all.png");

    // /scans/fracture projection max
    Volume volume9(path_frac);
    volume9.load();
    Projection project9(volume9);
    const char *model9="avg"; //avg, min
    std::string model_str9(model9);
    Image projected_image9 = project9.chosen_projection("avg", 1, 1300);
    std::string pure_name9 = projected_image9.get_name_in_path(projected_image9.save_name);
    projected_image9.save("./../Output/fracture/" + pure_name9 + "_" + model_str9 + "_all.png");

    /*
    Volume res_volume_con_gaus("./../3d_median_blur_0.4");
    // volume2.load();3d_median_blur_0.4
    Projection project_con_gaus(res_volume_con_gaus);
    const char *model_con_gaus="max"; //avg, min
    std::string model_str_con_gaus(model_con_gaus);
    Image projected_image_con_gaus = project_con_gaus.chosen_projection("max", 1, 265);
    std::string pure_name_con_gaus = projected_image_con_gaus.get_name_in_path(projected_image_con_gaus.save_name);
    projected_image_con_gaus.save("./../Output/confuciusornis/" + pure_name_con_gaus + "_" + model_str_con_gaus + "_gaussian_all.png");*/

    Volume volume4_pm(path_con);
    volume4_pm.load();
    Projection project4_pm(volume4_pm);
    const char *model4_pm="max"; //avg, min
    std::string model_str4_pm(model4_pm);
    Image projected_image4_pm = project4_pm.chosen_projection("max", 10, 70);
    std::string pure_name4_pm = projected_image4_pm.get_name_in_path(projected_image4_pm.save_name);
    projected_image4_pm.save("./../Output/confuciusornis/" + pure_name4_pm + "_" + model_str4_pm + "_10_70.png");

    Volume volume5_pmin(path_con);
    volume5_pmin.load();
    Projection project5_pmin(volume5_pmin);
    const char *model5_pmin="min"; //avg, min
    std::string model_str5_pmin(model5_pmin);
    Image projected_image5_pmin = project5_pmin.chosen_projection("min", 10, 70);
    std::string pure_name5_pmin = projected_image5_pmin.get_name_in_path(projected_image5_pmin.save_name);
    projected_image5_pmin.save("./../Output/confuciusornis/" + pure_name5_pmin + "_" + model_str5_pmin + "_10_70.png");

    Volume volume6_pavg(path_con);
    volume6_pavg.load();
    Projection project6_pavg(volume6_pavg);
    const char *model6_pavg="avg"; //avg, min
    std::string model_str6_pavg(model6_pavg);
    Image projected_image6_pavg = project6_pavg.chosen_projection("min", 10, 70);
    std::string pure_name6_pavg = projected_image6_pavg.get_name_in_path(projected_image6_pavg.save_name);
    projected_image6_pavg.save("./../Output/confuciusornis/" + pure_name6_pavg + "_" + model_str6_pavg + "_10_70.png");

    Volume volume7_pmax(path_frac);
    volume7_pmax.load();
    Projection project7_pmax(volume7_pmax);
    const char *model7_pmax="max"; //avg, min
    std::string model_str7_pmax(model7_pmax);
    Image projected_image7_pmax = project7_pmax.chosen_projection("max", 276, 476);
    std::string pure_name7_pmax = projected_image7_pmax.get_name_in_path(projected_image7_pmax.save_name);
    projected_image7_pmax.save("./../Output/fracture/" + pure_name7_pmax + "_" + model_str7_pmax + "_600_800.png");

    Volume volume8_pmin(path_frac);
    volume8_pmin.load();
    Projection project8_pmin(volume8_pmin);
    const char *model8_pmin="min"; //avg, min
    std::string model_str8_pmin(model8_pmin);
    Image projected_image8_pmin = project8_pmin.chosen_projection("min", 276, 476);
    std::string pure_name8_pmin = projected_image8_pmin.get_name_in_path(projected_image8_pmin.save_name);
    projected_image8_pmin.save("./../Output/fracture/" + pure_name8_pmin + "_" + model_str8_pmin + "_600_800.png");

    Volume volume9_pavg(path_frac);
    volume9_pavg.load();
    Projection project9_pavg(volume9_pavg);
    const char *model9_pavg="avg"; //avg, min
    std::string model_str9_pavg(model9_pavg);
    Image projected_image9_pavg = project9_pavg.chosen_projection("avg", 276, 476);
    std::string pure_name9_pavg = projected_image9_pavg.get_name_in_path(projected_image9_pavg.save_name);
    projected_image9_pavg.save("./../Output/fracture/" + pure_name9_pavg + "_" + model_str9_pavg + "_600_800.png");

    // dimorphos.png
    const char *filename1 = "./../Images/dimorphos.png";
    Image image1(filename1);
    image1.load();
    // median blur
    Image i1 = filter.blur(image1, "median_blur", 3, 0);
    i1.save("./../Output/dimorphos/median_blur.png");
    // box blur
    Image i2 = filter.blur(image1, "box_blur", 3, 0);
    i2.save("./../Output/dimorphos/box_blur.png");
    // gaussian blur
    Image i3 = filter.blur(image1, "gaussian_blur", 3, 0.8);
    i3.save("./../Output/dimorphos/gaussian_blur.png");
    // robert_cross blur
    Image i4 = filter.edge_detection(image1, "robert_cross", "gaussian_blur", 3, 0.8);
    i4.save("./../Output/dimorphos/robert_cross_gaussian_blur.png");
    // scharr blur
    Image i5 = filter.edge_detection(image1, "scharr", "gaussian_blur", 3, 0.8);
    i5.save("./../Output/dimorphos/scharr_gaussian_blur.png");
    // scharr blur
    Image i6 = filter.edge_detection(image1, "sobel", "gaussian_blur", 3, 0.8);
    i6.save("./../Output/dimorphos/sobel_gaussian_blur.png");
    // prewitt
    Image i7 = filter.edge_detection(image1, "prewitt", "gaussian_blur", 3, 0.8);
    i7.save("./../Output/dimorphos/prewitt_gaussian_blur.png");
    Image i88 = filter.greyScale(image1);
    i88.save("./../Output/dimorphos/grayscale.png");
    Image i89 = filter.autoColorBalance(image1);
    i89.save("./../Output/dimorphos/autocolorbalance.png");
    Image i90 = filter.brightness(image1,100,false);
    i90.save("./../Output/dimorphos/brightness.png");
    Image i91 = filter.histogramEqualization(image1);
    i91.save("./../Output/dimorphos/histequ.png");

    // gracehopper.png
    const char *filename2 = "./../Images/gracehopper.png";
    Image image2(filename2);
    image2.load();
    // median blur
    Image i21 = filter.blur(image2, "median_blur", 3, 0);
    i21.save("./../Output/gracehopper/median_blur.png");
    // box blur
    Image i22 = filter.blur(image2, "box_blur", 3, 0);
    i22.save("./../Output/gracehopper/box_blur.png");
    // gaussian blur
    Image i23 = filter.blur(image2, "gaussian_blur", 3, 0.8);
    i23.save("./../Output/gracehopper/gaussian_blur.png");
    // robert_cross blur
    Image i24 = filter.edge_detection(image2, "robert_cross", "gaussian_blur", 3, 2);
    i24.save("./../Output/gracehopper/robert_cross_gaussian_blur.png");
    // scharr blur
    Image i25 = filter.edge_detection(image2, "scharr", "gaussian_blur", 3, 2);
    i25.save("./../Output/gracehopper/scharr_gaussian_blur.png");
    // scharr blur
    Image i26 = filter.edge_detection(image2, "sobel", "gaussian_blur", 3, 0.8);
    i26.save("./../Output/gracehopper/sobel_gaussian_blur.png");
    // prewitt
    Image i27 = filter.edge_detection(image2, "prewitt", "gaussian_blur", 3, 2);
    i27.save("./../Output/gracehopper/prewitt_gaussian_blur.png");
    Image i84 = filter.greyScale(image2);
    i84.save("./../Output/gracehopper/grayscale.png");
    // scharr blur
    Image i85 = filter.autoColorBalance(image2);
    i85.save("./../Output/gracehopper/autocolorbalance.png");
    // scharr blur
    Image i86 = filter.brightness(image2,100,false);
    i86.save("./../Output/gracehopper/brightness.png");
    // prewitt
    Image i87 = filter.histogramEqualization(image2);
    i87.save("./../Output/gracehopper/histequ.png");

    // stinkbug.png
    const char *filename3 = "./../Images/stinkbug.png";
    Image image3(filename3);
    image3.load();
    // median blur
    Image i31 = filter.blur(image3, "median_blur", 5, 0);
    i31.save("./../Output/stinkbug/median_blur.png");
    // box blur
    Image i32 = filter.blur(image3, "box_blur", 5, 0);
    i32.save("./../Output/stinkbug/box_blur.png");
    // gaussian blur
    Image i33 = filter.blur(image3, "gaussian_blur", 5, 0.8);
    i33.save("./../Output/stinkbug/gaussian_blur.png");
    // robert_cross blur
    Image i34 = filter.edge_detection(image3, "robert_cross", "gaussian_blur", 5, 0.8);
    i34.save("./../Output/stinkbug/robert_cross_gaussian_blur.png");
    // scharr blur
    Image i35 = filter.edge_detection(image3, "scharr", "gaussian_blur", 5, 0.8);
    i35.save("./../Output/stinkbug/scharr_gaussian_blur.png");
    // scharr blur
    Image i36 = filter.edge_detection(image3, "sobel", "gaussian_blur", 5, 0.8);
    i36.save("./../Output/stinkbug/sobel_gaussian_blur.png");
    // prewitt
    Image i37 = filter.edge_detection(image3, "prewitt", "gaussian_blur", 5, 0.8);
    i37.save("./../Output/stinkbug/prewitt_gaussian_blur.png");
    Image i80 = filter.greyScale(image3);
    i80.save("./../Output/stinkbug/grayscale.png");
    // scharr blur
    Image i81 = filter.autoColorBalance(image3);
    i81.save("./../Output/stinkbug/autocolorbalance.png");
    // scharr blur
    Image i82 = filter.brightness(image3,100,false);
    i82.save("./../Output/stinkbug/brightness.png");
    // prewitt
    Image i83 = filter.histogramEqualization(image3);
    i83.save("./../Output/stinkbug/histequ.png");

    // tienshan.png
    const char *filename4 = "./../Images/tienshan.png";
    Image image4(filename4);
    image4.load();
    // median blur
    Image i41 = filter.blur(image4, "median_blur", 5, 0);
    i41.save("./../Output/tienshan/median_blur.png");
    // box blur
    Image i42 = filter.blur(image4, "box_blur", 5, 0);
    i42.save("./../Output/tienshan/box_blur.png");
    // gaussian blur
    Image i43 = filter.blur(image4, "gaussian_blur", 5, 0.8);
    i43.save("./../Output/tienshan/gaussian_blur.png");
    // robert_cross blur
    Image i44 = filter.edge_detection(image4, "robert_cross", "gaussian_blur", 5, 0.8);
    i44.save("./../Output/tienshan/robert_cross_gaussian_blur.png");
    // scharr blur
    Image i45 = filter.edge_detection(image4, "scharr", "gaussian_blur", 5, 0.8);
    i45.save("./../Output/tienshan/scharr_gaussian_blur.png");
    // scharr blur
    Image i46 = filter.edge_detection(image4, "sobel", "gaussian_blur", 5, 0.8);
    i46.save("./../Output/tienshan/sobel_gaussian_blur.png");
    // prewitt
    Image i47 = filter.edge_detection(image4, "prewitt", "gaussian_blur", 5, 0.8);
    i47.save("./../Output/tienshan/prewitt_gaussian_blur.png");
    Image i76 = filter.greyScale(image4);
    i76.save("./../Output/tienshan/grayscale.png");
    // scharr blur
    Image i77 = filter.autoColorBalance(image4);
    i77.save("./../Output/tienshan/autocolorbalance.png");
    // scharr blur
    Image i78 = filter.brightness(image4,100,false);
    i78.save("./../Output/tienshan/brightness.png");
    // prewitt
    Image i79 = filter.histogramEqualization(image4);
    i79.save("./../Output/tienshan/histequ.png");

    // vh_anatomy.png
    const char *filename5 = "./../Images/vh_anatomy.png";
    Image image5(filename5);
    image5.load();
    // median blur
    Image i51 = filter.blur(image5, "median_blur", 5, 0);
    i51.save("./../Output/vh_anatomy/median_blur.png");
    // box blur
    Image i52 = filter.blur(image5, "box_blur", 5, 0);
    i52.save("./../Output/vh_anatomy/box_blur.png");
    // gaussian blur
    Image i53 = filter.blur(image5, "gaussian_blur", 5, 0.8);
    i53.save("./../Output/vh_anatomy/gaussian_blur.png");
    // robert_cross blur
    Image i54 = filter.edge_detection(image5, "robert_cross", "gaussian_blur", 5, 0.8);
    i54.save("./../Output/vh_anatomy/robert_cross_gaussian_blur.png");
    // scharr blur
    Image i55 = filter.edge_detection(image5, "scharr", "gaussian_blur", 5, 0.8);
    i55.save("./../Output/vh_anatomy/scharr_gaussian_blur.png");
    // scharr blur
    Image i56 = filter.edge_detection(image5, "sobel", "gaussian_blur", 5, 0.8);
    i56.save("./../Output/vh_anatomy/sobel_gaussian_blur.png");
    // prewitt
    Image i57 = filter.edge_detection(image5, "prewitt", "gaussian_blur", 5, 0.8);
    i57.save("./../Output/vh_anatomy/prewitt_gaussian_blur.png");
    Image i72 = filter.greyScale(image5);
    i72.save("./../Output/vh_anatomy/grayscale.png");
    // scharr blur
    Image i73 = filter.autoColorBalance(image5);
    i73.save("./../Output/vh_anatomy/autocolorbalance.png");
    // scharr blur
    Image i74 = filter.brightness(image5,100,false);
    i74.save("./../Output/vh_anatomy/brightness.png");
    // prewitt
    Image i75 = filter.histogramEqualization(image5);
    i75.save("./../Output/vh_anatomy/histequ.png");


    // vh_ct.png
    const char *filename6 = "./../Images/vh_ct.png";
    Image image6(filename6);
    image6.load();
    // median blur
    Image i61 = filter.blur(image6, "median_blur", 5, 0);
    i61.save("./../Output/vh_ct/median_blur.png");
    // box blur
    Image i62 = filter.blur(image6, "box_blur",3, 0);
    i62.save("./../Output/vh_ct/box_blur.png");
    // gaussian blur
    Image i63 = filter.blur(image6, "gaussian_blur", 5, 0.8);
    i63.save("./../Output/vh_ct/gaussian_blur.png");
    // robert_cross blur
    Image i64 = filter.edge_detection(image6, "robert_cross", "gaussian_blur", 5, 0.8);
    i64.save("./../Output/vh_ct/robert_cross_gaussian_blur.png");
    // scharr blur
    Image i65 = filter.edge_detection(image6, "scharr", "gaussian_blur", 5, 0.8);
    i65.save("./../Output/vh_ct/scharr_gaussian_blur.png");
    // scharr blur
    Image i66 = filter.edge_detection(image6, "sobel", "gaussian_blur", 5, 0.8);
    i66.save("./../Output/vh_ct/sobel_gaussian_blur.png");
    // prewitt
    Image i67 = filter.edge_detection(image6, "prewitt", "gaussian_blur", 5, 0.8);
    i67.save("./../Output/vh_ct/prewitt_gaussian_blur.png");
    Image i68 = filter.greyScale(image6);
    i68.save("./../Output/vh_ct/grayscale.png");
    // scharr blur
    Image i69 = filter.autoColorBalance(image6);
    i69.save("./../Output/vh_ct/autocolorbalance.png");
    // scharr blur
    Image i70 = filter.brightness(image6,100,false);
    i70.save("./../Output/vh_ct/brightness.png");
    // prewitt
    Image i71 = filter.histogramEqualization(image6);
    i71.save("./../Output/vh_ct/histequ.png");


    auto end = chrono::high_resolution_clock::now(); // End timer for vector insertion
    double elapsed_seconds_v = chrono::duration_cast<chrono::duration<double>>(end - start).count();
    cout << "Elapsed time: " << elapsed_seconds_v << endl;
}
