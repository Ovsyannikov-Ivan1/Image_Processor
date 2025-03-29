#include <gtest/gtest.h>
#include "filters/Filter.h"

constexpr int ImageSize = 5;
constexpr float WhiteValue = 1.0f;

class DummyFilter : public Filter {
public:
    void Apply(Image& image) const override {
        image.SetPixel(0, 0, Pixel(WhiteValue, WhiteValue, WhiteValue));
    }
};

TEST(FilterTest, DummyFilterTest) {
    Image img(ImageSize, ImageSize);
    DummyFilter filter;
    filter.Apply(img);
    Pixel p = img.GetPixel(0, 0);
    EXPECT_FLOAT_EQ(p.r, WhiteValue);
    EXPECT_FLOAT_EQ(p.g, WhiteValue);
    EXPECT_FLOAT_EQ(p.b, WhiteValue);
}
