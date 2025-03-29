#pragma once

#include "Filter.h"

class GrayscaleFilter : public Filter {
public:
    void Apply(Image& image) const override;
};
