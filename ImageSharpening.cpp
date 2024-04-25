#include "ImageSharpening.h"
#include <iostream>

// Default constructor
ImageSharpening::ImageSharpening() {
	blur = new double* [3];
	for (int i = 0; i < 3; i++) {
		blur[i] = new double[3];
		for (int j = 0; j < 3; j++) {
			blur[i][j] = 1.0 / 9.0;
		}
	}
}
ImageSharpening::~ImageSharpening() {
	for (int i = 0; i < 3; i++) {
		delete[] blur[i];
	}
	delete[] blur;
	blur = nullptr;
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k) {
    ImageMatrix inputimage = input_image;
    Convolution convo(blur, 3, 3, 1, true);
    ImageMatrix BlurredImg = convo.convolve(inputimage);
    for (int i = 0; i < BlurredImg.get_height(); i++) {
        for (int j = 0; j < BlurredImg.get_width(); j++) {
            double value = inputimage.get_data(i, j) + k * (inputimage.get_data(i, j) - BlurredImg.get_data(i, j));
            if (value < 0.0) {
                value = 0.0;
            }
            else if (value > 255.0) {
                value = 255.0;
            }
            inputimage.set_data(i, j, value);
        }
    }

    return inputimage;
}
