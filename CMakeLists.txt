cmake_minimum_required(VERSION 3.12)
project(l4d2_base)  # Replace l4d2_base with the actual project name

# Set the build platform to x86
set(CMAKE_GENERATOR_PLATFORM x86)
# Set the build configuration to Release
set(CMAKE_BUILD_TYPE Release)
# Set PlatformToolset to v143
set(CMAKE_GENERATOR_TOOLSET "v143")
# Set WindowsTargetPlatformVersion to 10.0
set(CMAKE_SYSTEM_VERSION 10.0)
# Set UseWindowsSDK to true
set(CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION "10.0")
# Set CharacterSet to Unicode
add_definitions(-DUNICODE -D_UNICODE)
# Set UseUnicodeCharacterSet to true
add_definitions(-D_UNICODE)
# Set NoWarn to **
add_definitions(-D_CRT_SECURE_NO_WARNINGS)
# Set LanguageStandard to c++17
set(CMAKE_CXX_STANDARD 17)

# Source files
# Set the source files directory
set(SOURCE_FILES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(CMAKE_WARN_DEPRECATED FALSE)
add_compile_options(-w)

# Use GLOB_RECURSE to find all source files in subdirectories
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_FILES_DIR}/*.cpp)

# Use GLOB_RECURSE to find all source files in subdirectories
file(GLOB_RECURSE HEADER_FILES ${SOURCE_FILES_DIR}/*.h)
file(GLOB_RECURSE SOURCE_FILES1 ${SOURCE_FILES_DIR}/*.hpp)
file(GLOB_RECURSE SOURCE_FILES2 ${SOURCE_FILES_DIR}/*.c)

# Add the library target
add_library(l4d2_base SHARED ${SOURCE_FILES} ${HEADER_FILES} ${SOURCE_FILES1} ${SOURCE_FILES2})

# Set C++ standard
set_target_properties(l4d2_base PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME "pol" # Replace pol with the actual library name
)
