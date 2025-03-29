#pragma once

#include "Filter.h"

class PixelationFilter : public Filter {
public:
    explicit PixelationFilter(size_t block_size);
    void Apply(Image& image) const override;

private:
    size_t block_size_;
};
