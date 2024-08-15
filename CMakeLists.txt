cmake_minimum_required(VERSION 3.13)

project(algebra LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_COMPILER  "/usr/bin/clang++")

add_subdirectory(NumType)
