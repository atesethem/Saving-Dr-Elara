#include "EncodeMessage.h"
#include <cmath>
#include <vector>
#include <bitset>
#include <iostream>
// Default Constructor
EncodeMessage::EncodeMessage() {
}

// Destructor
EncodeMessage::~EncodeMessage() {
}

ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix& img, const std::string& message, const std::vector<std::pair<int, int>>& positions) {
    ImageMatrix encodedImage = img;
    std::string transformedMessage = transformMessage(message);
    int shiftAmount = transformedMessage.length() / 2;
    transformedMessage = circularshift(transformedMessage, shiftAmount);

    int messageIndex = 0;
    for (int messageIndex = 0; messageIndex < transformedMessage.size(); messageIndex++)
    {
        if (messageIndex * 7 >= positions.size()) break;
        char currentChar = transformedMessage[messageIndex];
        std::bitset<7> charBits(currentChar);
        for (int bitIndex = 0; bitIndex < 7; bitIndex++) {
            if (messageIndex * 7 + bitIndex >= positions.size()) break;
            auto position = positions.at(messageIndex * 7 + bitIndex);
            int x = position.first;
            int y = position.second;
            int pixelValue = static_cast<int>(encodedImage.get_data(x, y));
            pixelValue &= ~1;
            pixelValue |= charBits[bitIndex];
            encodedImage.set_data(x, y, static_cast<double>(pixelValue));


        }

    }


    return encodedImage;
}

std::string EncodeMessage::transformMessage(const std::string& message) {
    std::string transformedMessage = message;

    for (size_t i = 0; i < transformedMessage.length(); i++) {
        if (isprime(i)) {
            int asciiValue = static_cast<int>(transformedMessage[i]);
            int fibonacciNumber = calculateFibonacci(i);
            asciiValue += fibonacciNumber;

            if (asciiValue <= 32) {
                asciiValue += 33;
            }
            else if (asciiValue >= 127) {
                asciiValue = 126;
            }

            transformedMessage[i] = static_cast<char>(asciiValue);
        }
    }

    return transformedMessage;
}

bool EncodeMessage::isprime(int num) {
    if (num < 2) return false;
    bool bIsPrime = true;
    for (int i = 2; i < num; i++)
    {
        if (num % i == 0) bIsPrime = false;
    }

    return bIsPrime;
}

int EncodeMessage::calculateFibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;

    int a = 0;
    int b = 1;
    int c;

    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }

    return b;
}

std::string EncodeMessage::circularshift(const std::string& message, int shiftAmount) {
    int len = message.length();
    std::string shiftedMessage = message;

    for (int i = 0; i < len; i++) {
        shiftedMessage[(i + shiftAmount) % len] = message[i];
    }

    return shiftedMessage;
}