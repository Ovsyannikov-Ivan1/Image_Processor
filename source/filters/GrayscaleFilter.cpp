#include "filters/GrayscaleFilter.h"

void GrayscaleFilter::Apply(Image& image) const {
    constexpr float RedCoeff = 0.299f;
    constexpr float GreenCoeff = 0.587f;
    constexpr float BlueCoeff = 0.114f;

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Pixel pixel = image.GetPixel(x, y);
            float gray = RedCoeff * pixel.r + GreenCoeff * pixel.g + BlueCoeff * pixel.b;
            image.SetPixel(x, y, Pixel(gray, gray, gray));
        }
    }
}
