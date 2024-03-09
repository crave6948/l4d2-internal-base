cmake_minimum_required(VERSION 3.12)
project(l4d2_base)  # Replace l4d2_base with the actual project name
# Source files
# Set the source files directory
set(SOURCE_FILES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Use GLOB_RECURSE to find all source files in subdirectories
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_FILES_DIR}/*.cpp)

# Use GLOB_RECURSE to find all source files in subdirectories
file(GLOB_RECURSE HEADER_FILES ${SOURCE_FILES_DIR}/*.h)
file(GLOB_RECURSE SOURCE_FILES1 ${SOURCE_FILES_DIR}/*.hpp)
file(GLOB_RECURSE SOURCE_FILES2 ${SOURCE_FILES_DIR}/*.c)

# Add the library target
add_library(l4d2_base_dll SHARED ${SOURCE_FILES} ${HEADER_FILES} ${SOURCE_FILES1} ${SOURCE_FILES2})

# Set C++ standard
set_target_properties(l4d2_base_dll PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Set the output directory for the DLL file
set_target_properties(l4d2_base_dll PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin
)
