# https://jacquesh.github.io/post/basic-cmake/
# Project definition
cmake_minimum_required(VERSION 3.8.0)
project(path_tracer)

# Source directorioes and files
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin)

# Executable output directory
set(EXECUTABLE_OUTPUT_PATH ${BIN_DIR})

# All needed source files
file(GLOB_RECURSE SOURCES
	${SRC_DIR}/*.cpp
	${SRC_DIR}/*.h
)

set(STB_INCLUDE ${LIB_DIR}/stb)

# Mian executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
)

# Include directories
include_directories(${PROJECT_NAME}
    ${STB_INCLUDE}
)
