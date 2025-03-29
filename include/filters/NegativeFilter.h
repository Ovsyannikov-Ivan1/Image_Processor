#pragma once

#include "Filter.h"

class NegativeFilter : public Filter {
public:
    void Apply(Image& image) const override;
};
