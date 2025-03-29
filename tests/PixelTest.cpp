#include <gtest/gtest.h>
#include "bmp/Image.h"

namespace {
constexpr float PixelR = 1.2f;
constexpr float PixelG = -0.5f;
constexpr float PixelB = 0.7f;
}  // namespace

TEST(PixelTest, DefaultConstructor) {
    const Pixel p;
    EXPECT_FLOAT_EQ(p.r, 0.0f);
    EXPECT_FLOAT_EQ(p.g, 0.0f);
    EXPECT_FLOAT_EQ(p.b, 0.0f);
}

TEST(PixelTest, ParameterizedConstructorClamp) {
    const Pixel p(PixelR, PixelG, PixelB);
    EXPECT_FLOAT_EQ(p.r, 1.0f);
    EXPECT_FLOAT_EQ(p.g, 0.0f);
    EXPECT_FLOAT_EQ(p.b, PixelB);
}
