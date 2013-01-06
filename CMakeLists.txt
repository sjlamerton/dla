cmake_minimum_required(VERSION 2.6)
project(dla)

# Enable C++11 in GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

find_package(Boost REQUIRED COMPONENTS program_options)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# Add our files to some variables
set(source dla.cpp input.cpp)
set(headers dla.h input.h output.h)

# Create our executable
add_executable(dla ${source} ${headers})
target_link_libraries(dla ${Boost_LIBRARIES})
