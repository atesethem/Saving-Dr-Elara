#include "EdgeDetector.h"
#include <cmath>
#include <iostream>
#include <vector>
// Default constructor
EdgeDetector::EdgeDetector() {
    Gx = new double* [3];
    Gy = new double* [3];

    for (int i = 0; i < 3; i++) {
        Gx[i] = new double[3];
        Gy[i] = new double[3];
    }

  
    Gx[0][0] = -1; Gx[0][1] = 0; Gx[0][2] = 1;
    Gx[1][0] = -2; Gx[1][1] = 0; Gx[1][2] = 2;
    Gx[2][0] = -1; Gx[2][1] = 0; Gx[2][2] = 1;

    Gy[0][0] = -1; Gy[0][1] = -2; Gy[0][2] = -1;
    Gy[1][0] = 0; Gy[1][1] = 0; Gy[1][2] = 0;
    Gy[2][0] = 1; Gy[2][1] = 2; Gy[2][2] = 1;
}

// Destructor
EdgeDetector::~EdgeDetector() {
    if (Gx != nullptr) {
        for (int i = 0; i < 3; i++) {
            delete[] Gx[i];
        }
        delete[] Gx;
        Gx = nullptr;
    }
    if (Gy != nullptr) {
        for (int i = 0; i < 3; i++) {
            delete[] Gy[i];
        }
        delete[] Gy;
        Gy = nullptr;
    }
}


std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image) {
 
    ImageMatrix inputimage = input_image;
    Convolution forx(Gx, 3, 3, 1, true);
    
    Convolution fory(Gy, 3, 3, 1, true);
    ImageMatrix xresult = forx.convolve(inputimage);
    ImageMatrix yresult = fory.convolve(inputimage);
    std::vector<std::pair<int, int>> EdgePixels;
    
    xresult.WriteToText("ea");
    int numberofpixels = input_image.get_height() * input_image.get_width();
    double sum = 0;
    std::cout << 3;
    for (int i = 0; i < input_image.get_height(); i++) {
        for (int j = 0; j < input_image.get_width(); j++) {
            sum += sqrt(xresult.get_data()[i][j] * xresult.get_data()[i][j] + yresult.get_data()[i][j] * yresult.get_data()[i][j]);
        }
    }
    double threshold = sum / numberofpixels;
    for (int i = 0; i < input_image.get_height(); i++) {
        for (int j = 0; j < input_image.get_width(); j++) {
            double gradient = sqrt(xresult.get_data()[i][j] * xresult.get_data()[i][j] + yresult.get_data()[i][j] * yresult.get_data()[i][j]);
            if (gradient > threshold) {
                EdgePixels.push_back(std::make_pair(i, j));
            }
        }
    } 
   
    for (const auto& pixel : EdgePixels) {
        int x = pixel.first;
        int y = pixel.second;
        std::cout << "Pixel Coordinates: (" << x << ", " << y << ")" << std::endl;
    }
    return EdgePixels;
}