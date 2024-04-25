
#ifndef CONVOLUTION_H
#define CONVOLUTION_H
#include "ImageMatrix.h"
class Convolution
{
public:
	Convolution();
	Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad);
	Convolution(const Convolution& other);
	ImageMatrix convolve(const ImageMatrix& input_image) const;
	~Convolution();
	Convolution& operator=(const Convolution& other);
private:
	double** kernel;
	int kernelheight;
	int kernelwidth;
	int stride;
	bool paddle;

};

#endif // CONVOLUTION_H


