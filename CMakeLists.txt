# Define the project name
project(Elevator_System)

# Specify the minimum version of CMake required to build this project
cmake_minimum_required(VERSION 3.7)

# Set the C++ standard to C++11
add_definitions(-std=c++11)

# Define compiler flags
set(CXX_FLAGS "-Wall") # Enable all compiler's warning messages
# Set the CMake C++ compiler flags to the previously defined flags
set(CMAKE_CXX_FLAGS "${CXX_FLAGS}")

# List of source files to be compiled
set(sources src/elevator.cpp src/elevator_sim.cpp)

# Specify directories where header files are located
include_directories(include)

# Create the executable from the specified source files
add_executable(elev_sys_sim ${sources})
