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

    # TokenType's .cpp files
    set(TokenType_src_files
    "${TokenType_SOURCE_DIR}/src/TokenType.cpp"
    )


    # TokenType is a simple data structure, so consists of one .h file
    add_library(TokenType STATIC ${TokenType_src_files})
    target_include_directories(TokenType PUBLIC ${TokenType_include_dirs})
endif(NOT TARGET TokenType)