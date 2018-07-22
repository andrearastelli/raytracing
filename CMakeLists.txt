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

add_subdirectory(ext/googletest)

add_subdirectory(src)
include_directories(${CMAKE_SOURCE_DIR}/src)

target_compile_features(raytracing PUBLIC cxx_std_17)

enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/src/*.cpp)

if(NOT MSVC)
    foreach(_test_file ${TEST_SRC_FILES})
        get_filename_component(_test_name ${_test_file} NAME_WE)
        add_executable(${_test_name} ${_test_file})
        add_dependencies(${_test_name} gtest)
        target_link_libraries(${_test_name} gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
        add_test(NAME ${_test_name} COMMAND ${_test_name} WORKING_DIRECTORY "${CMAKE_HOME_DIRECTORY}/bin")
        message("${CMAKE_HOME_DIRECTORY}/bin/${_test_name}")
    endforeach()
endif()
