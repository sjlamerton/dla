cmake_minimum_required(VERSION 2.6)
project(dla)

# Enable C++11 in GCC
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=c++11)
endif()

if(MSVC)
    set(BOOST_ROOT "C:/Programming/boost_1_54_0")
    set(Boost_USE_STATIC_LIBS ON)
endif()

find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIRS})
add_definitions(${PNG_DEFINITIONS})

find_package (Threads)

# Add our files to some variables
set(source dla.cpp grid.cpp input.cpp output.cpp particle_inserter.cpp)
set(headers dla.h grid.h input.h output.h particle_inserter.h)

# Create our executable
add_executable(dla ${source} ${headers})
target_link_libraries(dla ${Boost_LIBRARIES} ${PNG_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
