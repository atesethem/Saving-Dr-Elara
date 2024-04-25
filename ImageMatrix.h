#ifndef IMAGE_MATRIX_H
#define IMAGE_MATRIX_H

#include <string>

#include "ImageLoader.h"

class ImageMatrix
{
public:
    ImageMatrix();
    ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth);
    ImageMatrix(const std::string& filepath);
    double** get_data() const; 
    double get_data(int i, int j) const;
    void WriteToText(std::string Header);
    int get_height() const;
    int get_width() const;
    void set_data(int i, int j, double value) const;
    ImageMatrix& operator=(const ImageMatrix& other);
    ImageMatrix(int imgheight, int imgwidth);
    ImageMatrix operator+(const ImageMatrix& other) const;
    ImageMatrix operator-(const ImageMatrix& other) const;
    ImageMatrix operator*(const double& scalar) const;;
    ImageMatrix(const ImageMatrix& other);
    ~ImageMatrix();

private:
    // Private member variables to store the image data
    double** data; // 2D array to store image data
    int height; // Height of the matrix
    int width; // Width of the matrix
};

#endif // IMAGE_MATRIX_H

