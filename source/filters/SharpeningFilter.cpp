#include "filters/SharpeningFilter.h"

void SharpeningFilter::Apply(Image& image) const {
    Image result(image.GetWidth(), image.GetHeight());
    const int kernel[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};

    for (size_t y = 1; y < image.GetHeight() - 1; ++y) {
        for (size_t x = 1; x < image.GetWidth() - 1; ++x) {
            float r = 0.0f;
            float g = 0.0f;
            float b = 0.0f;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    Pixel p = image.GetPixel(x + kx, y + ky);
                    int weight = kernel[ky + 1][kx + 1];
                    r += p.r * static_cast<float>(weight);
                    g += p.g * static_cast<float>(weight);
                    b += p.b * static_cast<float>(weight);
                }
            }

            result.SetPixel(x, y, Pixel(r, g, b));
        }
    }

    image = result;
}
