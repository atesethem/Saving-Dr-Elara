

#include "ImageMatrix.h"

#include <fstream>
#include <iostream>
ImageMatrix::ImageMatrix() {
    data = 0, height = 0, width = 0;
}
ImageMatrix::ImageMatrix(const std::string& filepath) {
    ImageLoader imageLoader(filepath);
    height = imageLoader.getHeight();
    width = imageLoader.getWidth();
    data = new double* [height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    double** imageData = imageLoader.getImageData();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = imageData[i][j];
        }
    }

}
ImageMatrix::ImageMatrix(int imgheight, int imgwidth) : height(imgheight), width(imgwidth)
{
    data = new double* [height];
    for (int i = 0; i < height; i++) {
        data[i] = new double[width];
        for (int j = 0; j < width; j++)
        {
            data[i][j] = 0.0;
        }
    }
}
// Parameterized constructor - direct initialization with 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {
    data = new double* [height];
    for (int i = 0; i < height; i++)
    {
        data[i] = new double[width];
        for (int j = 0; j < width; j++)
        {
            data[i][j] = inputMatrix[i][j];
        }
    }
}
//copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix& other) : height(other.height), width(other.width) {
    data = new double* [height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
}
ImageMatrix::~ImageMatrix() //belki pixel in datasý da silinmesi gerekebilir
{
    if (data != nullptr)
    {
        for (int i = 0; i < height; i++)
        {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}
void ImageMatrix::WriteToText(std::string Header) /// SÝLÝNECEK
{
    std::cout << 2;
    std::ofstream File("C:\\Users\\biret\\OneDrive\\Masaüstü\\ethem\\c++\\firstassignment\\mainpart\\mainpart\\CurrentArray.txt");
    File << Header << std::endl;
    File << "\t";
    for (int w = 0; w < width; w++)
    {
        File << w << "\t";
    }
    File << std::endl;
    for (int h = 0; h < height; h++)
    {
        File << h << "\t";
        for (int w = 0; w < width; w++)
        {
            File << data[h][w] << "\t";
        }
        File << std::endl;
    }
    File << std::endl;
    File.close();
}
int ImageMatrix::get_height() const {
    return height;
}
int ImageMatrix::get_width() const {
    return width;
}
double** ImageMatrix::get_data() const {
    return data;
}
double ImageMatrix::get_data(int i, int j) const {
    return data[i][j];
}
void ImageMatrix::set_data(int i, int j, double value) const {
    data[i][j] = value;


}
// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix& other) {
    if (this == &other) {
        return *this; 
    }
    for (int i = 0; i < height; ++i) {
        delete[] data[i];
    }
    delete[] data;
    height = other.height;
    width = other.width;
    data = new double* [height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
        for (int j = 0; j < width; ++j) {
            data[i][j] = other.data[i][j];
        }
    }
    return *this; 
}



// Overloaded operators

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix& other) const {
    if (this == &other) {
        return *this;
    }
    std::cout << 3;

    ImageMatrix result(height, width);
    std::cout << 4;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = data[i][j] + other.data[i][j];
        }
    }

    return result;
}


// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix& other) const {
    if (this == &other) {
        return *this; 
    }

    ImageMatrix result(height, width);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = data[i][j] - other.data[i][j];
        }
    }

    return result;
}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const {
    ImageMatrix result(height, width);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            result.data[i][j] = data[i][j] * scalar;
        }
    }
    return result;
}