########################################################################
#
# CMake build script for TokenType.

if (NOT TARGET TokenType)
    cmake_minimum_required(VERSION 3.22)

    project(TokenType LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


    # Where TokenType's .h files can be found.
    set(TokenType_include_dirs
        "${TokenType_SOURCE_DIR}/include/TokenType"
    )
    # TokenType's .cpp files
    set(TokenType_src_files 
    )

    add_library(TokenType INTERFACE)
    target_include_directories(TokenType INTERFACE ${TokenType_include_dirs})

    ########################################################################
    #
    # TokenType's tests.

    option(TokenType_test_enable "Build all of Lexer's tests." ON)

    if (${BUILD_TESTING} AND ${TokenType_test_enable})
        find_package(GTest REQUIRED)
        add_executable(TokenType_test ${TokenType_SOURCE_DIR}/test/TokenType_test.cpp)
        target_link_libraries(TokenType_test TokenType GTest::gtest_main)
        add_test(NAME TokenType_test COMMAND TokenType_test)
    endif()
endif(NOT TARGET TokenType)