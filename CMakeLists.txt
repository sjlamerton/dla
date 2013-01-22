cmake_minimum_required(VERSION 2.6)
project(dla)

# Enable C++11 in GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIRS})
add_definitions(${PNG_DEFINITIONS})

# Add our files to some variables
set(source dla.cpp input.cpp output.cpp)
set(headers dla.h input.h output.h)

# Create our executable
add_executable(dla ${source} ${headers})
target_link_libraries(dla ${Boost_LIBRARIES} ${PNG_LIBRARIES})
