########################################################################
#
# CMake build script for Real.

if (NOT TARGET Real)
    cmake_minimum_required(VERSION 3.22)

    project(Real LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


    # Where Real's .h files can be found.
    # Real is a template module, so .cpp files includes in the end of .h files
    set(Real_include_dirs
        "${Real_SOURCE_DIR}/include/Real"
    )

    add_library(Real INTERFACE)
    target_include_directories(Real INTERFACE ${Real_include_dirs})


    ########################################################################
    #
    # Real's tests.

    option(Real_test_enable "Build all of Real's tests." ON)

    if (${BUILD_TESTING} AND ${Real_test_enable})
        find_package(GTest REQUIRED)
        add_executable(Real_test ${Real_SOURCE_DIR}/test/Real_Double_Operators_test.cpp)
        target_link_libraries(Real_test Real GTest::gtest_main)
        add_test(NAME Real_test COMMAND Real_test)
    endif()
endif (NOT TARGET Real)