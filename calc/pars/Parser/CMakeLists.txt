########################################################################
#
# CMake build script for Parser.

if (NOT TARGET Parser)
    cmake_minimum_required(VERSION 3.22)

    project(Parser LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


    # Where Parser's .h files can be found.
    set(Parser_include_dirs
        "${Parser_SOURCE_DIR}/include/Parser"
        "${Parser_SOURCE_DIR}/include/Parser/impl/bison"
    )
    # Where BisonParserGenerated's .h files can be found.
    set(BisonParserGenerated_include_dirs
        "${Parser_SOURCE_DIR}/include/Parser/impl/bison"
    )
    # Parser's .cpp files
    set(Parser_src_files
    )
    # BisonParserGenerated's .cpp files
    set(BisonParserGenerated
    "${Parser_SOURCE_DIR}/src/impl/bison/BisonParserGenerated.cpp"
    )


    # Bison paser generator 
    find_package(BISON)
    BISON_TARGET(BisonParserGenerated src/impl/bison/Bison_Parser.y
    ${Parser_SOURCE_DIR}/src/impl/bison/BisonParserGenerated.cpp
    DEFINES_FILE ${Parser_SOURCE_DIR}/include/Parser/impl/bison/BisonParserGenerated.h)

    add_library(BisonParserGenerated STATIC ${BisonParserGenerated})
    target_include_directories(BisonParserGenerated PUBLIC ${BisonParserGenerated_include_dirs})

    add_library(Parser INTERFACE ${Parser_src_files})
    target_include_directories(Parser INTERFACE ${Parser_include_dirs})
    target_link_libraries(Parser INTERFACE BisonParserGenerated)

    ########################################################################
    #
    # Parser's dependencies.

    add_subdirectory(../../tok/TokenType build/tok/TokenType)
    add_subdirectory(../../../num/NumType build/num/NumType)
    target_link_libraries(BisonParserGenerated PUBLIC TokenType NumType)
    target_link_libraries(Parser INTERFACE TokenType NumType)

    ########################################################################
    #
    # Parser's tests.

    option(Parser_test_enable "Build all of Parser's tests." ON)

    if (${BUILD_TESTING} AND ${Parser_test_enable})
        find_package(GTest REQUIRED)
        add_executable(Parser_test ${Parser_SOURCE_DIR}/test/Parser_test.cpp)
        target_link_libraries(Parser_test Parser GTest::gtest_main)
        add_test(NAME Parser_test COMMAND Parser_test)
    endif()
endif(NOT TARGET Parser)