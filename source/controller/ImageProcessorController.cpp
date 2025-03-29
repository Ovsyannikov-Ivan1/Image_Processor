#include "controller/ImageProcessorController.h"
#include "bmp/BMP.h"
#include "filters/CropFilter.h"
#include "filters/GrayscaleFilter.h"
#include "filters/NegativeFilter.h"
#include "filters/SharpeningFilter.h"
#include "filters/EdgeDetectionFilter.h"
#include "filters/GaussianBlurFilter.h"
#include "filters/PixelationFilter.h"
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <cctype>

namespace {
bool IsNumber(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}
}  // namespace

void ImageProcessorController::Process(int argc, char* argv[]) {
    if (argc < 3) {
        throw std::runtime_error("Usage: <input.bmp> <output.bmp> [filters]");
    }

    const std::string input_file = argv[1];
    const std::string output_file = argv[2];

    std::vector<std::shared_ptr<Filter>> filters;

    for (int i = 3; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-gs") {
            filters.push_back(std::make_shared<GrayscaleFilter>());
        } else if (arg == "-neg") {
            filters.push_back(std::make_shared<NegativeFilter>());
        } else if (arg == "-sharp") {
            filters.push_back(std::make_shared<SharpeningFilter>());
        } else if (arg == "-edge") {
            if (i + 1 >= argc) {
                throw std::runtime_error("Missing threshold value for -edge");
            }

            std::string threshold_str = argv[++i];
            if (!IsNumber(threshold_str)) {
                throw std::runtime_error("Threshold for -edge must be a numeric value");
            }

            float threshold = std::stof(threshold_str);
            if (threshold <= 0.0f || threshold > 1.0f) {
                throw std::runtime_error("Threshold for -edge must be in range (0, 1]");
            }
            filters.push_back(std::make_shared<EdgeDetectionFilter>(threshold));
        } else if (arg == "-blur") {
            if (i + 1 >= argc) {
                throw std::runtime_error("Missing sigma value for -blur");
            }

            std::string sigma_str = argv[++i];
            if (!IsNumber(sigma_str)) {
                throw std::runtime_error("Sigma for -blur must be numeric");
            }

            float sigma = std::stof(sigma_str);
            if (sigma <= 0.0f) {
                throw std::runtime_error("Sigma for -blur must be positive");
            }
            filters.push_back(std::make_shared<GaussianBlurFilter>(sigma));
        } else if (arg == "-crop") {
            if (i + 2 >= argc) {
                throw std::runtime_error("Missing width/height for -crop");
            }

            std::string crop_width_str = argv[++i];
            std::string crop_height_str = argv[++i];
            if (!IsNumber(crop_width_str) || !IsNumber(crop_height_str)) {
                throw std::runtime_error("Crop width/height must be numeric");
            }

            int crop_width_int = std::stoi(crop_width_str);
            int crop_height_int = std::stoi(crop_height_str);

            if (crop_width_int <= 0 || crop_height_int <= 0) {
                throw std::runtime_error("Crop width/height must be positive");
            }
            filters.push_back(std::make_shared<CropFilter>(static_cast<size_t>(crop_width_int),
                                                           static_cast<size_t>(crop_height_int)));
        } else if (arg == "-pixel") {
            if (i + 1 >= argc) {
                throw std::runtime_error("Missing block size for pixelation");
            }

            std::string block_size_str = argv[++i];
            if (!IsNumber(block_size_str)) {
                throw std::runtime_error("Block size for pixelation must be numeric");
            }

            int block_size_int = std::stoi(block_size_str);
            if (block_size_int <= 0) {
                throw std::runtime_error("Block size must be positive");
            }
            filters.push_back(std::make_shared<PixelationFilter>(static_cast<size_t>(block_size_int)));
        } else {
            throw std::runtime_error("Unknown filter: " + arg);
        }
    }

    Image image(0, 0);
    bmp::BMP::Read(input_file, image);

    for (const auto& filter : filters) {
        filter->Apply(image);
    }

    bmp::BMP::Write(output_file, image);

    std::cout << "Image successfully processed!" << std::endl;
}
