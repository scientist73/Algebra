cmake_minimum_required(VERSION 3.13)

project(NumType LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


add_library(NumType STATIC src/NumType.cpp  src/impl/alg_t/Real_NumType.cpp src/impl/alg_t/Complex_NumType.cpp src/impl/scalar/SimpleScalarType.cpp src/impl/alg_t/NumTypeOperators.cpp)

target_include_directories(NumType PUBLIC include/NumType)
target_include_directories(NumType PUBLIC ../include/algebra)
target_include_directories(NumType PRIVATE include/NumType/impl/alg_t)
target_include_directories(NumType PRIVATE include/NumType/impl/scalar)


enable_testing()
find_package(GTest REQUIRED) # sudo apt-get install libgtest-dev

add_executable(NumType_test test/NumType_test.cpp)
target_link_libraries(NumType_test NumType GTest::gtest_main)
