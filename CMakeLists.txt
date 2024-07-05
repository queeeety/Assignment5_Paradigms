cmake_minimum_required(VERSION 3.20)
project(Assignment5)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES wrapper.cpp main.cpp)

add_library(exprtk STATIC ${SOURCE_FILES})

target_include_directories(exprtk PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(mainExecutable main.cpp)

target_link_libraries(mainExecutable exprtk)