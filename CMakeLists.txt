cmake_minimum_required(VERSION 3.10)
project(exprtk_lib)

set(CMAKE_CXX_STANDARD 11)


set(SOURCE_FILES wrapper.cpp)

add_library(exprtk STATIC ${SOURCE_FILES})

target_include_directories(exprtk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})