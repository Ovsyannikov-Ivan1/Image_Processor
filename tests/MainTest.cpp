#include <gtest/gtest.h>
#include "controller/ImageProcessorController.h"

TEST(MainTest, NoArguments) {
    char arg0[] = "image_processor";
    char* argv[] = {arg0};
    EXPECT_THROW(
        {
            ImageProcessorController controller;
            controller.Process(1, argv);
        },
        std::runtime_error);
}

TEST(MainTest, UnknownFilter) {
    char arg0[] = "image_processor";
    char arg1[] = "in.bmp";
    char arg2[] = "out.bmp";
    char arg3[] = "-unknown";
    char* argv[] = {arg0, arg1, arg2, arg3};
    EXPECT_THROW(
        {
            ImageProcessorController controller;
            controller.Process(4, argv);
        },
        std::runtime_error);
}
