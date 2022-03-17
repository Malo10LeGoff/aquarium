cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED  True)

set(CMAKE_BUILD_TYPE Debug)

# set the project name
project(Aquarium)

# Add the source and library subdirectories
add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(test)