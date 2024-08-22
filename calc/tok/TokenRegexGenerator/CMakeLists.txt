########################################################################
#
# CMake build script for TokenRegexGenerator.

if (NOT TARGET TokenRegexGenerator)
    cmake_minimum_required(VERSION 3.22)

    project(TokenRegexGenerator LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


    # Where TokenRegexGenerator's .h files can be found.
    set(TokenRegexGenerator_include_dirs
        "${TokenRegexGenerator_SOURCE_DIR}/include/TokenRegexGenerator"
    )
    # TokenRegexGenerator's .cpp files
    set(TokenRegexGenerator_src_files
    "${TokenRegexGenerator_SOURCE_DIR}/src/TokenRegexGenerator.cpp"
    )

    add_library(TokenRegexGenerator STATIC ${TokenRegexGenerator_src_files})
    target_include_directories(TokenRegexGenerator PUBLIC ${TokenRegexGenerator_include_dirs})

    ########################################################################
    #
    # TokenRegexGenerator's dependencies.

    add_subdirectory(../TokenType build/TokenType)
    target_link_libraries(TokenRegexGenerator PRIVATE TokenType)

    ########################################################################
    #
    # TokenRegexGenerator's tests.

    option(TokenRegexGenerator_test_enable "Build all of TokenRegexGenerator's tests." ON)

    if (${BUILD_TESTING} AND ${TokenRegexGenerator_test_enable})
        find_package(GTest REQUIRED)
        add_executable(TokenRegexGenerator_test ${TokenRegexGenerator_SOURCE_DIR}/test/TokenRegexGenerator_test.cpp)
        target_link_libraries(TokenRegexGenerator_test TokenRegexGenerator GTest::gtest_main)
        add_test(NAME TokenRegexGenerator_test COMMAND TokenRegexGenerator_test)
    endif()
endif(NOT TARGET TokenRegexGenerator)