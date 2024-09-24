########################################################################
#
# CMake build script for AlgebraException.

if (NOT TARGET AlgebraException)
    cmake_minimum_required(VERSION 3.22)

    project(AlgebraException LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 20)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


    # Where AlgebraException's .h files can be found.
    set(AlgebraException_include_dirs
        "${AlgebraException_SOURCE_DIR}/include/AlgebraException"
    )
    # AlgebraException's .cpp files
    set(AlgebraException_src_files
    "${AlgebraException_SOURCE_DIR}/src/AlgebraException.cpp"
    )

    add_library(AlgebraException STATIC ${AlgebraException_src_files})
    target_include_directories(AlgebraException PUBLIC ${AlgebraException_include_dirs})

    ########################################################################
    #
    # AlgebraException's dependencies.


    ########################################################################
    #
    # AlgebraException's tests.

    option(AlgebraException_test_enable "Build all of AlgebraException's tests." ON)

    if (${BUILD_TESTING} AND ${AlgebraException_test_enable})
        find_package(GTest REQUIRED)
        add_executable(AlgebraException_test ${AlgebraException_SOURCE_DIR}/test/AlgebraException_test.cpp)
        target_link_libraries(AlgebraException_test AlgebraException GTest::gtest_main)
        add_test(NAME AlgebraException_test COMMAND AlgebraException_test)
    endif()
endif(NOT TARGET AlgebraException)