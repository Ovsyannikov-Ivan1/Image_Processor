#include "filters/GaussianBlurFilter.h"
#include <cmath>
#include <cstdint>
#include <algorithm>

const float K_PI_VALUE = 3.14159265358979323846f;
const float K_RADIUS_MULTIPLIER = 3.0f;
const float K_TWO = 2.0f;
const int K_MIN_COLOR_VALUE = 0;
const int K_MAX_COLOR_VALUE = 255;

GaussianBlurFilter::GaussianBlurFilter(float sigma) : sigma_(sigma) {
    CreateKernel();
}

void GaussianBlurFilter::CreateKernel() {
    int radius = static_cast<int>(std::ceil(sigma_ * K_RADIUS_MULTIPLIER));
    kernel_.resize(radius * 2 + 1);
    float sum = 0.0f;

    for (int i = -radius; i <= radius; ++i) {
        float exponent = -(static_cast<float>(i) * static_cast<float>(i)) / (K_TWO * sigma_ * sigma_);
        float value = std::exp(exponent) / (std::sqrt(K_TWO * K_PI_VALUE) * sigma_);
        kernel_[i + radius] = value;
        sum += value;
    }

    for (auto& value : kernel_) {
        value /= sum;
    }
}

void GaussianBlurFilter::Apply(Image& image) const {
    Image temp_image = image;
    int radius = static_cast<int>(kernel_.size() / 2);

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            float red_sum = 0.0f;
            float green_sum = 0.0f;
            float blue_sum = 0.0f;

            for (int kx = -radius; kx <= radius; ++kx) {
                int x_pos = std::clamp(static_cast<int>(x) + kx, 0, static_cast<int>(image.GetWidth()) - 1);
                const Pixel current_pixel = image.GetPixel(x_pos, y);

                red_sum += static_cast<float>(current_pixel.r) * kernel_[kx + radius];
                green_sum += static_cast<float>(current_pixel.g) * kernel_[kx + radius];
                blue_sum += static_cast<float>(current_pixel.b) * kernel_[kx + radius];
            }

            temp_image.SetPixel(
                x, y,
                Pixel(
                    static_cast<uint8_t>(std::clamp(static_cast<int>(red_sum), K_MIN_COLOR_VALUE, K_MAX_COLOR_VALUE)),
                    static_cast<uint8_t>(std::clamp(static_cast<int>(green_sum), K_MIN_COLOR_VALUE, K_MAX_COLOR_VALUE)),
                    static_cast<uint8_t>(
                        std::clamp(static_cast<int>(blue_sum), K_MIN_COLOR_VALUE, K_MAX_COLOR_VALUE))));
        }
    }

    for (size_t y = 0; y < image.GetHeight(); ++y) {
        for (size_t x = 0; x < image.GetWidth(); ++x) {
            float red_sum = 0.0f;
            float green_sum = 0.0f;
            float blue_sum = 0.0f;

            for (int ky = -radius; ky <= radius; ++ky) {
                int y_pos = std::clamp(static_cast<int>(y) + ky, 0, static_cast<int>(image.GetHeight()) - 1);
                const Pixel current_pixel = temp_image.GetPixel(x, y_pos);

                red_sum += static_cast<float>(current_pixel.r) * kernel_[ky + radius];
                green_sum += static_cast<float>(current_pixel.g) * kernel_[ky + radius];
                blue_sum += static_cast<float>(current_pixel.b) * kernel_[ky + radius];
            }

            image.SetPixel(
                x, y,
                Pixel(
                    static_cast<uint8_t>(std::clamp(static_cast<int>(red_sum), K_MIN_COLOR_VALUE, K_MAX_COLOR_VALUE)),
                    static_cast<uint8_t>(std::clamp(static_cast<int>(green_sum), K_MIN_COLOR_VALUE, K_MAX_COLOR_VALUE)),
                    static_cast<uint8_t>(
                        std::clamp(static_cast<int>(blue_sum), K_MIN_COLOR_VALUE, K_MAX_COLOR_VALUE))));
        }
    }
}
