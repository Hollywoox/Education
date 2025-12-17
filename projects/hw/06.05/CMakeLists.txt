####################################################################

cmake_minimum_required(VERSION 3.28)

####################################################################

project(06.05 VERSION 24.02.06 LANGUAGES CXX)

####################################################################

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_STANDARD_REQUIRED True)

####################################################################

find_package(Boost 1.85 REQUIRED COMPONENTS)

####################################################################

include_directories(${Boost_INCLUDE_DIRS})

####################################################################

# First dynamic library
add_library(shared_v1 SHARED libshared_v1.cpp)

target_compile_options(shared_v1 PRIVATE -Wall -Wextra -Wpedantic -O0)

####################################################################

# Second dynamic library
add_library(shared_v2 SHARED libshared_v2.cpp)

target_compile_options(shared_v2 PRIVATE -Wall -Wextra -Wpedantic -O0)

####################################################################

# Executable
add_executable(06.05 06.05.cpp)

target_compile_options(06.05 PRIVATE -Wall -Wextra -Wpedantic -O0)

target_link_libraries(06.05 PUBLIC ${Boost_LIBRARIES})

####################################################################
