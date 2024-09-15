########################################################################
#
# CMake build script for Calculator.

if (NOT TARGET Calculator)
    cmake_minimum_required(VERSION 3.22)

    project(Calculator LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


    # Where Calculator's .h files can be found.
    set(Calculator_include_dirs
        "${Calculator_SOURCE_DIR}/include/Calculator"
    )

    add_library(Calculator INTERFACE)
    target_include_directories(Calculator INTERFACE ${Calculator_include_dirs})


    ########################################################################
    #
    # Calculator's dependencies.

    add_subdirectory(../../num/NumType build/NumType)
    add_subdirectory(../lex/Lexer build/lex/Lexer)
    add_subdirectory(../pars/Parser build/pars/Parser)
    add_subdirectory(../tok/TokenType build/tok/TokenType)

    target_link_libraries(Calculator INTERFACE NumType Lexer Parser TokenType)

    ########################################################################
    #
    # Calculator's tests.

    option(Calculator_test_enable "Build all of Calculator's tests." ON)

    if (${BUILD_TESTING} AND ${Calculator_test_enable})
        find_package(GTest REQUIRED) # sudo apt-get install libgtest-dev
        add_executable(Calculator_test ${Calculator_SOURCE_DIR}/test/Calculator_test.cpp)
        target_link_libraries(Calculator_test Calculator GTest::gtest_main)
        add_test(NAME Calculator_test COMMAND Calculator_test)
    endif()
endif (NOT TARGET Calculator)