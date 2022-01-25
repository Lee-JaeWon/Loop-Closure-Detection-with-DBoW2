cmake_minimum_required(VERSION 3.1)
project(mono_vo)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenCV 3 REQUIRED)
find_package(DBoW2 REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS} ${DBoW2_INCLUDE_DIRS})

add_executable(mono_vo main.cpp)

#message(FATAL_ERROR ${OpenCV_LIBS})
target_link_libraries( mono_vo ${OpenCV_LIBS} ${DBoW2_LIBS})
