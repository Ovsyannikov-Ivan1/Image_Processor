#pragma once

#include <string>
#include <vector>
#include <memory>
#include "filters/Filter.h"

class ImageProcessorController {
public:
    void Process(int argc, char* argv[]);

private:
    std::string input_file_;
    std::string output_file_;
    std::vector<std::shared_ptr<Filter>> filters_;
};
