#include "filters/PixelationFilter.h"

PixelationFilter::PixelationFilter(size_t block_size) : block_size_(block_size) {
}

void PixelationFilter::Apply(Image& image) const {
    for (size_t y = 0; y < image.GetHeight(); y += block_size_) {
        for (size_t x = 0; x < image.GetWidth(); x += block_size_) {
            float sum_r = 0.0f;
            float sum_g = 0.0f;
            float sum_b = 0.0f;
            size_t pixels_count = 0;

            for (size_t dy = 0; dy < block_size_ && (y + dy) < image.GetHeight(); ++dy) {
                for (size_t dx = 0; dx < block_size_ && (x + dx) < image.GetWidth(); ++dx) {
                    Pixel p = image.GetPixel(x + dx, y + dy);
                    sum_r += p.r;
                    sum_g += p.g;
                    sum_b += p.b;
                    ++pixels_count;
                }
            }

            Pixel average(sum_r / static_cast<float>(pixels_count), sum_g / static_cast<float>(pixels_count),
                          sum_b / static_cast<float>(pixels_count));

            for (size_t dy = 0; dy < block_size_ && (y + dy) < image.GetHeight(); ++dy) {
                for (size_t dx = 0; dx < block_size_ && (x + dx) < image.GetWidth(); ++dx) {
                    image.SetPixel(x + dx, y + dy, average);
                }
            }
        }
    }
}
