########################################################################
#
# CMake build script for ScalarType.

if (NOT TARGET ScalarType)
    cmake_minimum_required(VERSION 3.22)

    project(ScalarType LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


    # Where ScalarType's .h files can be found.
    set(ScalarType_include_dirs
        "${ScalarType_SOURCE_DIR}/include/ScalarType"
    )
    # ScalarType's .cpp files
    set(ScalarType_src_files
    "${ScalarType_SOURCE_DIR}/src/StdScalarType.cpp"
    )

    add_library(ScalarType STATIC ${ScalarType_src_files})
    target_include_directories(ScalarType PUBLIC ${ScalarType_include_dirs})


    ########################################################################
    #
    # ScalarType's tests.

    option(ScalarType_test_enable "Build all of ScalarType's tests." ON)

    if (${BUILD_TESTING} AND ${ScalarType_test_enable})
        find_package(GTest REQUIRED)
        add_executable(ScalarType_test ${ScalarType_SOURCE_DIR}/test/ScalarType_test.cpp)
        target_link_libraries(ScalarType_test ScalarType GTest::gtest_main)
        add_test(NAME ScalarType_test COMMAND ScalarType_test)
    endif()
endif(NOT TARGET ScalarType)