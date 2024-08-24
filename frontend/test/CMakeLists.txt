# Assuming this file is located in frontend/test
cmake_minimum_required(VERSION 3.20)
project(test_lexer)

# Add Google Test to the project
find_package(GTest REQUIRED)

# Add test source files
add_executable(test_lexer test_lexer.cpp)

# Link the test executable with Google Test and pthread
target_link_libraries(test_lexer PRIVATE GTest::GTest GTest::Main frontend_lib)

# Enable testing
include(GoogleTest)
gtest_discover_tests(test_lexer)
