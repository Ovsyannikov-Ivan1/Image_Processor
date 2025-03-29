#pragma once

#include "Filter.h"
#include "filters/GrayscaleFilter.h"

class EdgeDetectionFilter : public Filter {
public:
    explicit EdgeDetectionFilter(float threshold);
    void Apply(Image& image) const override;

private:
    float threshold_;
};
