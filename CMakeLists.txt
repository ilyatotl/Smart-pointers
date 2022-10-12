cmake_minimum_required(VERSION 3.22)
project(pointers)

set(CMAKE_CXX_STANDARD 17)

add_executable(pointers main.cpp SharedPtr.h UniquePtr.h)
