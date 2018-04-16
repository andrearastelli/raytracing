cmake_minimum_required(VERSION 3.0)

project(raytracing)

# Set C++ to use the C++17 standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# C++ 17 for Visual Studio build
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)


set(CMAKE_INSTALL_PREFIX "./build")


file(GLOB APP_SOURCE_FILES "./src/*.cpp")
add_executable(raytracing ${APP_SOURCE_FILES})
