#include "bmp/BMP.h"
#include <fstream>
#include <stdexcept>

void bmp::BMP::Read(const std::string& path, Image& image) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open BMP file");
    }

    BMPFileHeader file_header;
    BMPInfoHeader info_header;
    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    if (file_header.bfType != BmpSignature) {
        throw std::runtime_error("Not a BMP file");
    }

    const size_t width = info_header.biWidth;
    const size_t height = info_header.biHeight;
    const size_t padding = (4 - (width * 3) % 4) % 4;
    image = Image(width, height);

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            unsigned char b = 0;
            unsigned char g = 0;
            unsigned char r = 0;
            file.read(reinterpret_cast<char*>(&b), sizeof(b));
            file.read(reinterpret_cast<char*>(&g), sizeof(g));
            file.read(reinterpret_cast<char*>(&r), sizeof(r));

            image.SetPixel(static_cast<int>(x), static_cast<int>(y),
                           Pixel(static_cast<float>(r) * ColorNormalizer, static_cast<float>(g) * ColorNormalizer,
                                 static_cast<float>(b) * ColorNormalizer));
        }
        file.ignore(static_cast<std::streamsize>(padding));
    }
}

void bmp::BMP::Write(const std::string& path, const Image& image) {
    std::ofstream file(path, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Cannot open BMP file for writing");
    }

    const size_t width = image.GetWidth();
    const size_t height = image.GetHeight();
    const size_t row_size = width * 3;
    const size_t padding = (4 - (row_size % 4)) % 4;
    const size_t pixel_data_size = (row_size + padding) * height;
    const size_t file_size = FileHeaderSize + pixel_data_size;

    BMPFileHeader file_header = {BmpSignature, static_cast<uint32_t>(file_size), 0, 0, FileHeaderSize};
    BMPInfoHeader info_header = {InfoHeaderSize,
                                 static_cast<int32_t>(width),
                                 static_cast<int32_t>(height),
                                 ColorPlanes,
                                 BitsPerPixel,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0,
                                 0};

    file.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    file.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            Pixel p = image.GetPixel(static_cast<int>(x), static_cast<int>(y));

            const unsigned char blue = static_cast<unsigned char>(p.b * MaxColorValue);
            const unsigned char green = static_cast<unsigned char>(p.g * MaxColorValue);
            const unsigned char red = static_cast<unsigned char>(p.r * MaxColorValue);

            file.write(reinterpret_cast<const char*>(&blue), sizeof(blue));
            file.write(reinterpret_cast<const char*>(&green), sizeof(green));
            file.write(reinterpret_cast<const char*>(&red), sizeof(red));
        }
        for (size_t i = 0; i < padding; ++i) {
            file.put(0);
        }
    }
}