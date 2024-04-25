#include "ImageProcessor.h"

ImageProcessor::ImageProcessor()  {
	
}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix& img) {
	ImageMatrix newimage = img;
	ImageSharpening sharpened;
	ImageMatrix sharpenedimage = sharpened.sharpen(newimage,2);
	EdgeDetector edgedetector;
	pixels = edgedetector.detectEdges(sharpenedimage);
	DecodeMessage decoder;
	return decoder.decodeFromImage(sharpenedimage, pixels);
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix& img, const std::string& message) {
	ImageSharpening sharpened;
	ImageMatrix sharpenedimage = sharpened.sharpen(img, 2);
	EdgeDetector edgedetector;
	std::vector<std::pair<int, int>> thepixels = edgedetector.detectEdges(sharpenedimage);
	EncodeMessage encoder;
	ImageMatrix theimage = encoder.encodeMessageToImage(img, message, thepixels);
	return theimage;
}
