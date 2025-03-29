#include "bmp/Image.h"
#include <stdexcept>

Image::Image(size_t width, size_t height) : width_(width), height_(height), pixels_(width * height) {
}

size_t Image::GetWidth() const {
    return width_;
}

size_t Image::GetHeight() const {
    return height_;
}

Pixel Image::GetPixel(size_t x, size_t y) const {
    if (x >= width_ || y >= height_) {
        throw std::out_of_range("GetPixel: coordinates out of range");
    }
    return pixels_[y * width_ + x];
}

void Image::SetPixel(size_t x, size_t y, const Pixel& pixel) {
    if (x >= width_ || y >= height_) {
        throw std::out_of_range("SetPixel: coordinates out of range");
    }
    pixels_[y * width_ + x] = pixel;
}
