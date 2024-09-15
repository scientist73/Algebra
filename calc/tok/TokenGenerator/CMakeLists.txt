########################################################################
#
# CMake build script for TokenGenerator.

if (NOT TARGET TokenGenerator)
    cmake_minimum_required(VERSION 3.22)

    project(TokenGenerator LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


    # Where TokenGenerator's .h files can be found.
    set(TokenGenerator_include_dirs
        "${TokenGenerator_SOURCE_DIR}/include/TokenGenerator"
    )
    # TokenGenerator's .cpp files
    set(TokenGenerator_src_files
    "${TokenGenerator_SOURCE_DIR}/src/TokenGenerator.cpp"
    )

    add_library(TokenGenerator STATIC ${TokenGenerator_src_files})
    target_include_directories(TokenGenerator PUBLIC ${TokenGenerator_include_dirs})

    ########################################################################
    #
    # TokenGenerator's dependencies.

    add_subdirectory(../TokenType build/TokenType)
    target_link_libraries(TokenGenerator PRIVATE TokenType)

    ########################################################################
    #
    # TokenGenerator's tests.

    option(TokenGenerator_test_enable "Build all of TokenGenerator's tests." ON)

    if (${BUILD_TESTING} AND ${TokenGenerator_test_enable})
        find_package(GTest REQUIRED)
        add_executable(TokenGenerator_test ${TokenGenerator_SOURCE_DIR}/test/TokenGenerator_test.cpp)
        target_link_libraries(TokenGenerator_test TokenGenerator GTest::gtest_main)
        add_test(NAME TokenGenerator_test COMMAND TokenGenerator_test)
    endif()
endif(NOT TARGET TokenGenerator)