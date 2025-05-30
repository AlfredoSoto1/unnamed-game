cmake_minimum_required(VERSION 3.22)

project(rootproject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Library directories
set(GLFW_DIR "${CMAKE_SOURCE_DIR}/lib/glfw")
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/lib/glad")
set(VULKAN_DIR "${CMAKE_SOURCE_DIR}/lib/vulkan")

# Include header libraries
include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    "${GLFW_DIR}/include"
    "${GLAD_DIR}/include"
    "${VULKAN_DIR}/include"
)

# Set the specific glad source
set(GLAD_SRC "${GLAD_DIR}/src/glad.c")

# Set the static library path
set(GLFW_STATIC_LIB "${GLFW_DIR}/lib/glfw3.lib")
set(VULKAN_STATIC_LIB "${VULKAN_DIR}/lib/vulkan-1.lib")

# Add preprocessor definitions based on the build type
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DUR_DEBUG)
    add_definitions(-DASSETS_DIR=\"../../../assets/\")
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    add_definitions(-DUR_RELEASE)
    add_definitions(-DASSETS_DIR)
elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    add_definitions(-DUR_DIST)
    add_definitions(-DASSETS_DIR)
endif()

# Add the subdirectories for each project
add_subdirectory(uranium)
add_subdirectory(game)

if(WIN32)
    # Set specific flags for each configuration directly
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${CMAKE_PROJECT_NAME}  PRIVATE /Zi /Od /MDd)
        message("Debug build enabled")

    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(${CMAKE_PROJECT_NAME}  PRIVATE /MD /O2 /GS- /DNDEBUG)
        message("Release build enabled")

    elseif(CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
        target_compile_options(${CMAKE_PROJECT_NAME}  PRIVATE /O2 /DNDEBUG /OPT:REF /INCREMENTAL:NO /MD)
        set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES 
            LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
        message("Distribution build enabled")
    endif()
endif()
    
if(UNIX)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -g -O0 -DDEBUG)
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE -O2 -DNDEBUG)
    endif()

endif()