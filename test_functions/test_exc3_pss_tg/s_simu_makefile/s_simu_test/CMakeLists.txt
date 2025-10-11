cmake_minimum_required(VERSION 3.10)
project(TestProgram LANGUAGES CXX)

# ==========================
# Build Configuration
# ==========================
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2")

# ==========================
# Project Paths
# ==========================
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(INC_DIR "${CMAKE_SOURCE_DIR}/include")
set(EIGEN_DIR "${CMAKE_SOURCE_DIR}/third_party/eigen")

# Where to place the executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# ==========================
# Include Directories
# ==========================
include_directories(${INC_DIR})
include_directories(${EIGEN_DIR})

# ==========================
# Source Files
# ==========================
file(GLOB SRC_FILES "${SRC_DIR}/*.cpp")

# ==========================
# Executable Target
# ==========================
add_executable(test_program ${SRC_FILES})

# ==========================
# Output Info
# ==========================
message(STATUS "C++ Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Output binary: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_program")
message(STATUS "Eigen include path: ${EIGEN_DIR}")
