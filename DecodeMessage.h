#ifndef DECODE_MESSAGE_H
#define DECODE_MESSAGE_H

#include <string>
#include "ImageMatrix.h"


class DecodeMessage {
public:
   
    DecodeMessage(); // Default constructor
    ~DecodeMessage(); // Destructor

    std::string decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels);

private:
      
};

#endif // DECODE_MESSAGE_H
