########################################################################
#
# CMake build script for Complex.

if (NOT TARGET Complex)
    cmake_minimum_required(VERSION 3.22)

    project(Complex LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


    # Where Complex's .h files can be found.
    # Complex is a template module, so .cpp files includes in the end of .h files
    set(Complex_include_dirs
        "${Complex_SOURCE_DIR}/include/Complex"
    )

    add_library(Complex INTERFACE)
    target_include_directories(Complex INTERFACE ${Complex_include_dirs})


    ########################################################################
    #
    # Complex's tests.

    option(Complex_test_enable "Build all of Complex's tests." ON)

    if (${BUILD_TESTING} AND ${Complex_test_enable})
        find_package(GTest REQUIRED)
        add_executable(Complex_test ${Complex_SOURCE_DIR}/test/Complex_test.cpp)
        target_link_libraries(Complex_test Complex GTest::gtest_main)
        add_test(NAME Complex_test COMMAND Complex_test)
    endif()
endif (NOT TARGET Complex)