cmake_minimum_required(VERSION 3.5)
project(natiflect-test)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories("/System/Library/Frameworks/JavaVM.framework/Headers")

add_subdirectory(natiflect)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ~/Library/Java/Extensions/)
add_library(natiflect-test SHARED natiflect_test.h natiflect_test.cpp)
target_link_libraries (natiflect-test LINK_PUBLIC natiflect)
set_target_properties(natiflect natiflect-test
        PROPERTIES SUFFIX ".jnilib")
