cmake_minimum_required(VERSION 3.5)
project(natiflect)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("/System/Library/Frameworks/JavaVM.framework/Headers")

add_library(natiflect SHARED exception.h class.cpp class.h object.cpp object.h object_template_explicit.h utils.cpp utils.h)
target_include_directories(natiflect PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
