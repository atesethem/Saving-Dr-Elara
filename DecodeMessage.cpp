// DecodeMessage.cpp

#include "DecodeMessage.h"
#include "ImageMatrix.h" 

DecodeMessage::DecodeMessage() {
    // Constructor
}

DecodeMessage::~DecodeMessage() {
    // Destructor
}

std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels) {
    std::string bstring;
    ImageMatrix theimage = image;
    std::vector<std::pair<int, int>> myvector = edgePixels;
    for (auto pixel : edgePixels) {
        
        int pixelvalue = theimage.get_data(pixel.first, pixel.second);
        int lsb = pixelvalue & 1;
    
        bstring += std::to_string(lsb);
    }

  
    while (bstring.length() % 7 != 0) {
        bstring = "0" + bstring;
    }

    std::string asciistring;

    for (int i = 0; i < bstring.length(); i += 7) {
       
        std::string segment = bstring.substr(i, 7);
        int dvalue = std::stoi(segment, nullptr, 2);
        if (dvalue <= 32) {
            dvalue += 33;
        }
        else if (dvalue == 127) {
            dvalue = 126;
        }
        asciistring += static_cast<char>(dvalue);
    }
    return asciistring;
}