cmake_minimum_required(VERSION 3.0)

project(raytracing)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB APP_SOURCE_FILES "./src/*.cpp")
add_executable(raytracing ${APP_SOURCE_FILES})
