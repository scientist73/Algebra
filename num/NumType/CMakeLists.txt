########################################################################
#
# CMake build script for NumType.

if (NOT TARGET NumType)
    cmake_minimum_required(VERSION 3.22)

    project(NumType LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


    # Where NumType's .h files can be found.
    set(NumType_include_dirs
        "${NumType_SOURCE_DIR}/include/NumType"
        "${NumType_SOURCE_DIR}/include/NumType/impl"
    )

    add_library(NumType INTERFACE)
    target_include_directories(NumType INTERFACE ${NumType_include_dirs})


    ########################################################################
    #
    # NumType's dependencies.

    add_subdirectory(../../except/AlgebraException build/except/AlgebraException)

    add_subdirectory(../Real build/Real)
    add_subdirectory(../Complex build/Complex)
    add_subdirectory(../scalar/ScalarType build/scalar/ScalarType)

    target_link_libraries(NumType INTERFACE AlgebraException Complex Real ScalarType)

    ########################################################################
    #
    # NumType's tests.

    option(NumType_test_enable "Build all of NumType's tests." ON)

    if (${BUILD_TESTING} AND ${NumType_test_enable})
        find_package(GTest REQUIRED) # sudo apt-get install libgtest-dev
        add_executable(NumType_test ${NumType_SOURCE_DIR}/test/NumType_Double_Operators_test.cpp)
        target_link_libraries(NumType_test NumType GTest::gtest_main)
        add_test(NAME NumType_test COMMAND NumType_test)
    endif()
endif (NOT TARGET NumType)