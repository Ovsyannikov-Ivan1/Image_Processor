#pragma once

#include "bmp/Image.h"

class Filter {
public:
    virtual ~Filter() = default;
    virtual void Apply(Image& image) const = 0;
};
