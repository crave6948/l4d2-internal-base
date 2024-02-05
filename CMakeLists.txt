cmake_minimum_required(VERSION 3.12)
project(l4d2_base)  # Replace l4d2_base with the actual project name
# Source files
# Set the source files directory
set(SOURCE_FILES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Use GLOB_RECURSE to find all source files in subdirectories
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_FILES_DIR}/*.cpp)

# Use GLOB_RECURSE to find all source files in subdirectories
file(GLOB_RECURSE HEADER_FILES ${SOURCE_FILES_DIR}/*.h)

# Add the executable target
add_executable(l4d2_base ${SOURCE_FILES} ${HEADER_FILES})

# Set C++ standard
set_target_properties(l4d2_base PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# Include directories
target_include_directories(l4d2_base PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    # Add any additional include directories here
)

# Set compile options based on build configurations
target_compile_options(l4d2_base PRIVATE
    "$<$<CONFIG:Debug>: /Od /MDd /Zi /RTC1 /EHsc>"
    "$<$<CONFIG:Release>: /O2 /MD /EHsc>"
)

# Set additional compile definitions
target_compile_definitions(l4d2_base PRIVATE
    "$<$<CONFIG:Debug>: _DEBUG;_CONSOLE>"
    "$<$<CONFIG:Release>: NDEBUG;_CONSOLE>"
)

# Set link options based on build configurations
target_link_options(l4d2_base PRIVATE
    "$<$<CONFIG:Debug>: /DEBUG>"
    "$<$<CONFIG:Release>: /INCREMENTAL:NO /OPT:REF /OPT:ICF>"
)
