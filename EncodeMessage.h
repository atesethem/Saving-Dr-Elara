#ifndef ENCODE_MESSAGE_H
#define ENCODE_MESSAGE_H

#include <string>
#include <vector>
#include "ImageMatrix.h"

class EncodeMessage {
public:
    EncodeMessage();
    ~EncodeMessage();

    ImageMatrix encodeMessageToImage(const ImageMatrix& img, const std::string& message, const std::vector<std::pair<int, int>>& positions);


private:
    // Any private helper functions or variables if necessary
    std::string circularshift(const std::string& message, int shiftAmount);
    int calculateFibonacci(int n);
    bool isprime(int num);
    void embedMessage(ImageMatrix& image, const std::string& message, const std::vector<std::pair<int, int>>& positions);
    std::string transformMessage(const std::string& message);
};

#endif // ENCODE_MESSAGE_H
