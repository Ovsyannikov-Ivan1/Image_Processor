#include "controller/ImageProcessorController.h"
#include <iostream>

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;
    try {
        ImageProcessorController controller;
        controller.Process(argc, argv);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}