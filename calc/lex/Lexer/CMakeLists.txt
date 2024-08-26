########################################################################
#
# CMake build script for Lexer.

if (NOT TARGET Lexer)
    cmake_minimum_required(VERSION 3.22)

    project(Lexer LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


    # Where Lexer's .h files can be found.
    set(Lexer_include_dirs
        "${Lexer_SOURCE_DIR}/include/Lexer"
        "${Lexer_SOURCE_DIR}/include/Lexer/impl/flex"
    )
    # Lexer's .cpp files
    set(Lexer_src_files
    "${Lexer_SOURCE_DIR}/src/Lexer.cpp"
    "${Lexer_SOURCE_DIR}/src/impl/flex/Flex_Lexer.cpp"
    )

    # Flex lexer generator 
    find_package(FLEX)
    FLEX_TARGET(FlexLexer src/impl/flex/Flex_Lexer.l  ${Lexer_SOURCE_DIR}/src/impl/flex/Flex_Lexer.cpp)

    add_library(Lexer STATIC ${Lexer_src_files})
    target_include_directories(Lexer PUBLIC ${Lexer_include_dirs})

    ########################################################################
    #
    # Lexer's dependencies.

    add_subdirectory(../../tok/TokenType build/TokenType)
    add_subdirectory(../../tok/TokenGenerator build/TokenGenerator)
    target_link_libraries(Lexer PUBLIC TokenType TokenGenerator)

    ########################################################################
    #
    # Lexer's tests.

    option(Lexer_test_enable "Build all of Lexer's tests." ON)

    if (${BUILD_TESTING} AND ${Lexer_test_enable})
        find_package(GTest REQUIRED)
        add_executable(Lexer_test ${Lexer_SOURCE_DIR}/test/Lexer_test.cpp)
        target_link_libraries(Lexer_test Lexer GTest::gtest_main)
        add_test(NAME Lexer_test COMMAND Lexer_test)
    endif()
endif(NOT TARGET Lexer)