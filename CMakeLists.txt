cmake_minimum_required(VERSION 3.0)

project(raytracing)

# Set C++ to use the C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# C++ 17 for Visual Studio build
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_HOME_DIRECTORY}/bin")

include_directories(${CMAKE_SOURCE_DIR}/src)

add_subdirectory(src)

target_compile_features(raytracing PUBLIC cxx_std_17)

