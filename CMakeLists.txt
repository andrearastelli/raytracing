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

add_subdirectory(ext/googletest)
include_directories(ext/googletest/googletest/include)

add_subdirectory(src)

target_compile_features(raytracing PUBLIC cxx_std_17)

enable_testing()
include_directories()

file(GLOB TEST_SRC_FILES ${PROJECT_SOURCE_DIR}/tests/src/*.cpp)

foreach(_test_file ${TEST_SRC_FILES})
    get_filename_component(_test_name ${_test_file} NAME_WE)
    add_executable(${_test_name} ${_test_file})
    # add_dependencies(${_test_name} googletest.git)
    target_link_libraries(${_test_name} gtest gtest_main ${CMAKE_THREAD_LIBS_INIT})
    add_test(${_test_name} ${_test_name})
    set_tests_properties(${_test_name} PROPERTIES TIMEOUT 5)
    message("Test: ${_test_name}")
endforeach()
