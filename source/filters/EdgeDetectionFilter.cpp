#include "filters/EdgeDetectionFilter.h"

EdgeDetectionFilter::EdgeDetectionFilter(float threshold) : threshold_(threshold) {
}

void EdgeDetectionFilter::Apply(Image& image) const {
    GrayscaleFilter gray_filter;
    gray_filter.Apply(image);

    Image result(image.GetWidth(), image.GetHeight());
    const int kernel[3][3] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};

    for (size_t y = 1; y < image.GetHeight() - 1; ++y) {
        for (size_t x = 1; x < image.GetWidth() - 1; ++x) {
            float value = 0.0f;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    Pixel p = image.GetPixel(x + kx, y + ky);
                    value += p.r * static_cast<float>(kernel[ky + 1][kx + 1]);
                }
            }
            value = (value > threshold_) ? 1.0f : 0.0f;
            result.SetPixel(x, y, Pixel(value, value, value));
        }
    }

    image = result;
}
