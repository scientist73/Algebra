########################################################################
#
# CMake build script for NumType.

if (NOT TARGET NumType)
    cmake_minimum_required(VERSION 3.22)

    project(NumType LANGUAGES CXX)

    set(CMAKE_CXX_STANDARD 17)
    set(CMAKE_CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


    # Where NumType's .h files can be found.
    # NumType is a template module, so .cpp files includes in the end of .h files
    set(NumType_include_dirs
        "${NumType_SOURCE_DIR}/include/NumType"
        "${NumType_SOURCE_DIR}/include/NumType/impl"
    )

    add_library(NumType INTERFACE)
    target_include_directories(NumType INTERFACE ${NumType_include_dirs})

    add_subdirectory(../Real ../Real/build)
    add_subdirectory(../Complex ../Complex/build)
    add_subdirectory(../ScalarType ../ScalarType/build)

    target_link_libraries(NumType INTERFACE Complex Real ScalarType)

    ########################################################################
    #
    # NumType's tests.

    option(NumType_test_enable "Build all of NumType's tests." ON)

    if (${BUILD_TESTING} AND ${NumType_test_enable})
        find_package(GTest REQUIRED) # sudo apt-get install libgtest-dev
        add_executable(NumType_test ${NumType_SOURCE_DIR}/test/NumType_test.cpp)
        target_link_libraries(NumType_test NumType GTest::gtest_main)
        add_test(NAME NumType_test COMMAND NumType_test)
    endif()
endif (NOT TARGET NumType)