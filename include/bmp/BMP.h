#pragma once

#include <string>
#include <cstdint>
#include "Image.h"

namespace bmp {

constexpr uint32_t FileHeaderSize = 54;
constexpr uint32_t InfoHeaderSize = 40;
constexpr uint16_t ColorPlanes = 1;
constexpr uint16_t BitsPerPixel = 24;
constexpr uint32_t MaxColorValue = 255;
constexpr float ColorNormalizer = 1.0f / MaxColorValue;
constexpr uint16_t BmpSignature = 0x4D42;

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t bfType;
    uint32_t bfSize;
    uint16_t bfReserved1;
    uint16_t bfReserved2;
    uint32_t bfOffBits;
};

struct BMPInfoHeader {
    uint32_t biSize;
    int32_t biWidth;
    int32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    int32_t biXPelsPerMeter;
    int32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

class BMP {
public:
    static void Read(const std::string& path, Image& image);
    static void Write(const std::string& path, const Image& image);
};

}  // namespace bmp

inline Image ReadBMP(const std::string& path) {
    Image image(0, 0);
    bmp::BMP::Read(path, image);
    return image;
}

inline void WriteBMP(const std::string& path, const Image& image) {
    bmp::BMP::Write(path, image);
}
