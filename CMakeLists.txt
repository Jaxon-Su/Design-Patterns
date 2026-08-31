cmake_minimum_required(VERSION 3.16)
project(cpp_design_patterns_zh LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB EXAMPLE_FILES CONFIGURE_DEPENDS examples/*.cpp)

foreach(example_file IN LISTS EXAMPLE_FILES)
    get_filename_component(example_name "${example_file}" NAME_WE)
    add_executable("${example_name}" "${example_file}")
endforeach()
