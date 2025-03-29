#include "filters/NegativeFilter.h"

void NegativeFilter::Apply(Image& image) const {
    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            Pixel pixel = image.GetPixel(x, y);
            pixel.r = 1.0f - pixel.r;
            pixel.g = 1.0f - pixel.g;
            pixel.b = 1.0f - pixel.b;
            image.SetPixel(x, y, pixel);
        }
    }
}
