#pragma once

#include <vector>
#include <algorithm>

struct Pixel {
    float r;
    float g;
    float b;

    Pixel() : r(0.0f), g(0.0f), b(0.0f) {
    }

    Pixel(float red, float green, float blue)
        : r(std::clamp(red, 0.0f, 1.0f)), g(std::clamp(green, 0.0f, 1.0f)), b(std::clamp(blue, 0.0f, 1.0f)) {
    }
};

class Image {
public:
    Image(size_t width, size_t height);

    size_t GetWidth() const;
    size_t GetHeight() const;
    Pixel GetPixel(size_t x, size_t y) const;
    void SetPixel(size_t x, size_t y, const Pixel& pixel);

private:
    size_t width_;
    size_t height_;
    std::vector<Pixel> pixels_;
};
