########################################################################
#
# CMake build script for algebra.

cmake_minimum_required(VERSION 3.22)

project(algebra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")


########################################################################
#
# algebra's tests.

option(algebra_test_enable "Build all algebra's tests." ON)

if (${algebra_test_enable})
    include(CTest)
endif()

########################################################################
#
# algebra's modules build

add_subdirectory(num/Real)
add_subdirectory(num/Complex)
add_subdirectory(num/scalar/ScalarType)
add_subdirectory(num/NumType)

add_subdirectory(calc/tok/TokenType)

add_subdirectory(calc/lex/Lexer)
add_subdirectory(calc/pars/Parser)
add_subdirectory(calc/Calculator)
