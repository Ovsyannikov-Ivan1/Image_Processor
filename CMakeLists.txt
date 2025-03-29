cmake_minimum_required(VERSION 3.14)
project(image_processor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/include/bmp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/filters
    ${CMAKE_CURRENT_SOURCE_DIR}/include/controller
)

file(GLOB_RECURSE LIB_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp"
)
list(FILTER LIB_SOURCES EXCLUDE REGEX ".*image_processor\\.cpp$")

add_executable(image_processor
    ${CMAKE_CURRENT_SOURCE_DIR}/image_processor.cpp
    ${LIB_SOURCES}
)
target_link_libraries(image_processor pthread)

file(GLOB_RECURSE TEST_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
)

add_executable(runTests
    ${TEST_SOURCES}
    ${LIB_SOURCES}
)
target_link_libraries(runTests gtest gtest_main pthread)

enable_testing()
add_test(NAME UnitTests COMMAND runTests)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(image_processor PRIVATE -Wall -Wextra -Wpedantic -Werror)
    target_compile_options(runTests PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)