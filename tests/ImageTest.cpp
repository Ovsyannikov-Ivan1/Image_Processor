#include <gtest/gtest.h>
#include "bmp/Image.h"

constexpr int Width10 = 10;
constexpr int Height10 = 10;
constexpr int Width20 = 20;
constexpr int Height30 = 30;
constexpr float PixelR = 0.5f;
constexpr float PixelG = 0.3f;
constexpr float PixelB = 0.7f;
constexpr int PixelX = 5;
constexpr int PixelY = 5;
constexpr int OutOfBoundsX = 100;
constexpr int OutOfBoundsY = 100;

TEST(ImageTest, SetAndGetPixel) {
    Image image(Width10, Height10);
    Pixel p(PixelR, PixelG, PixelB);
    image.SetPixel(PixelX, PixelY, p);

    const Pixel result = image.GetPixel(PixelX, PixelY);
    EXPECT_FLOAT_EQ(result.r, PixelR);
    EXPECT_FLOAT_EQ(result.g, PixelG);
    EXPECT_FLOAT_EQ(result.b, PixelB);
}

TEST(ImageTest, OutOfBoundsAccess) {
    Image image(Width10, Height10);
    EXPECT_NO_THROW(image.GetPixel(0, 0));
    EXPECT_NO_THROW(image.GetPixel(Width10 - 1, Height10 - 1));
    EXPECT_THROW(image.GetPixel(OutOfBoundsX, OutOfBoundsY), std::out_of_range);
    EXPECT_THROW(image.SetPixel(OutOfBoundsX, OutOfBoundsY, Pixel(PixelR, PixelG, PixelB)), std::out_of_range);
}

TEST(ImageTest, Dimensions) {
    Image image(Width20, Height30);
    EXPECT_EQ(image.GetWidth(), Width20);
    EXPECT_EQ(image.GetHeight(), Height30);
}
