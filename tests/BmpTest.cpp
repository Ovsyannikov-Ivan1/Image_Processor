#include <gtest/gtest.h>
#include "filters/PixelationFilter.h"
#include "bmp/BMP.h"
#include <fstream>

constexpr float Tolerance = 1.0f / 255.0f;
constexpr int Width = 2;
constexpr int Height = 2;
constexpr float HalfValue = 0.5f;
constexpr float PixelValue1 = 0.2f;
constexpr float PixelValue2 = 0.3f;
constexpr float PixelValue3 = 0.4f;
constexpr std::streamsize InvalidSignatureLength = 7;

TEST(BMPTest, ReadWrite) {
    Image original(Width, Height);
    original.SetPixel(0, 0, Pixel(0.0f, 0.0f, 0.0f));
    original.SetPixel(1, 0, Pixel(1.0f, 1.0f, 1.0f));
    original.SetPixel(0, 1, Pixel(HalfValue, HalfValue, HalfValue));
    original.SetPixel(1, 1, Pixel(PixelValue1, PixelValue2, PixelValue3));

    const std::string temp_file = testing::TempDir() + "test.bmp";
    WriteBMP(temp_file, original);
    const Image read_back = ReadBMP(temp_file);

    EXPECT_EQ(read_back.GetWidth(), Width);
    EXPECT_EQ(read_back.GetHeight(), Height);
    EXPECT_NEAR(read_back.GetPixel(0, 0).r, 0.0f, Tolerance);
    EXPECT_NEAR(read_back.GetPixel(1, 0).r, 1.0f, Tolerance);
    EXPECT_NEAR(read_back.GetPixel(0, 1).r, HalfValue, Tolerance);
    EXPECT_NEAR(read_back.GetPixel(1, 1).r, PixelValue1, Tolerance);
}

TEST(BMPTest, ReadInvalid) {
    const std::string invalid_file = "non_existent.bmp";
    EXPECT_THROW(ReadBMP(invalid_file), std::runtime_error);

    const std::string temp_file = testing::TempDir() + "invalid.bmp";
    std::ofstream f(temp_file, std::ios::binary);
    f.write("INVALID", InvalidSignatureLength);
    f.close();
    EXPECT_THROW(ReadBMP(temp_file), std::runtime_error);
}
