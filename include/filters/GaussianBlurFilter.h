#pragma once

#include "Filter.h"
#include <vector>

class GaussianBlurFilter : public Filter {
public:
    explicit GaussianBlurFilter(float sigma);
    void Apply(Image& image) const override;

private:
    void CreateKernel();
    float sigma_;
    std::vector<float> kernel_;
};
