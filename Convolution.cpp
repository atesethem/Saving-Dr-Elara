#include "Convolution.h"
#include <iostream>

Convolution::Convolution() : kernel(nullptr), kernelheight(0), kernelwidth(0), stride(0), paddle(false) {}

Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool padding)
    : kernelheight(kh), kernelwidth(kw), stride(stride_val), paddle(padding) {
    kernel = new double* [kernelheight];
    for (int i = 0; i < kernelheight; i++) {
        kernel[i] = new double[kernelwidth];
        for (int j = 0; j < kernelwidth; j++) {
            kernel[i][j] = customKernel[i][j];
        }
    }
}

Convolution::~Convolution() {
    if (kernel != nullptr) {
        for (int i = 0; i < kernelheight; i++) {
            delete[] kernel[i];
        }
        delete[] kernel;
        kernel = nullptr;
    }
}

Convolution::Convolution(const Convolution& other)
    : kernelheight(other.kernelheight), kernelwidth(other.kernelwidth), stride(other.stride), paddle(other.paddle) {
    kernel = new double* [kernelheight];
    for (int i = 0; i < kernelheight; i++) {
        kernel[i] = new double[kernelwidth];
        for (int j = 0; j < kernelwidth; j++) {
            kernel[i][j] = other.kernel[i][j];
        }
    }
}

Convolution& Convolution::operator=(const Convolution& other) {
    if (this == &other) {
        return *this;
    }

  
    if (kernel != nullptr) {
        for (int i = 0; i < kernelheight; i++) {
            delete[] kernel[i];
        }
        delete[] kernel;
    }

    kernelheight = other.kernelheight;
    kernelwidth = other.kernelwidth;
    stride = other.stride;
    paddle = other.paddle;
    kernel = new double* [kernelheight];
    for (int j = 0; j < kernelheight; j++) {
        kernel[j] = new double[kernelwidth];
        for (int k = 0; k < kernelwidth; k++) {
            kernel[j][k] = other.kernel[j][k];
        }
    }
    return *this;
}

ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    int inputheight = input_image.get_height();
    int inputwidth = input_image.get_width();
    int stridevalue = stride;
    ImageMatrix inputimage = input_image;
    if (paddle) {
        inputheight += 2;
        inputwidth += 2;
  
        ImageMatrix paddedInput(inputheight, inputwidth);
        for (int i = 1; i < inputheight - 1; i++) {
            for (int j = 1; j < inputwidth - 1; j++) {
                paddedInput.set_data(i, j, inputimage.get_data(i - 1, j - 1));
            }
        }
        inputimage = paddedInput;
    }
    int outputHeight = (inputheight - kernelheight) / stridevalue + 1;
    int outputWidth = (inputwidth - kernelwidth) / stridevalue + 1;

    ImageMatrix outputImage(outputHeight, outputWidth);

    for (int i = 0; i < outputHeight; i++) {
        for (int j = 0; j < outputWidth; j++) {
            double sum = 0.0;
            for (int r = 0; r < kernelheight; r++) {
                for (int c = 0; c < kernelwidth; c++) {
                    int row = i * stridevalue + r;
                    int col = j * stridevalue + c;

                    if (row >= 0 && row < inputheight && col >= 0 && col < inputwidth) {
                        sum += kernel[r][c] * inputimage.get_data(row, col);
                    }
                }
            }
            outputImage.set_data(i, j, sum);
        }
    }
    return outputImage;
}