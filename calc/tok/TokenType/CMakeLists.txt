########################################################################
#
# CMake build script for TokenType.

if (NOT TARGET TokenType)
    cmake_minimum_required(VERSION 3.22)

    project(TokenType LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


    # Where TokenType's .h files can be found.
    set(TokenType_include_dirs
        "${TokenType_SOURCE_DIR}/include/TokenType"
    )

    # TokenType is a simple data structure, so consists of one .h file
    add_library(TokenType INTERFACE)
    target_include_directories(TokenType INTERFACE ${TokenType_include_dirs})
endif(NOT TARGET TokenType)