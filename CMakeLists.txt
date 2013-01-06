cmake_minimum_required(VERSION 2.6)
project(dla)

if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

# Add our files to some variables
set(source dla.cpp)
set(headers dla.h output.h)

# Create our executable called image
add_executable(dla ${source} ${headers})

