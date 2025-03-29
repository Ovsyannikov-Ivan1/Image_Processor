#pragma once

#include "Filter.h"

class SharpeningFilter : public Filter {
public:
    void Apply(Image& image) const override;
};
