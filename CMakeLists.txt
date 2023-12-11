cmake_minimum_required(VERSION 3.27)
project(Super_Tictactoe)

# Set C standard to C11
set(CMAKE_C_STANDARD 11)

# Directories

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(UTILS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/utils)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(BIN_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(OBJ_DIR ${CMAKE_CURRENT_SOURCE_DIR}/obj)

# Source files
set(SOURCES
    ${SOURCE_DIR}/main.c
    # SOURCES..
)

# Header files
include_directories(${INCLUDE_DIR})

# Executable
add_executable(executable ${SOURCES})

# Set output directories
set_target_properties(executable PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
    ARCHIVE_OUTPUT_DIRECTORY ${OBJ_DIR}
    LIBRARY_OUTPUT_DIRECTORY ${OBJ_DIR}
)

add_subdirectory(${TEST_DIR})
