# Uranium static library
project(uranium)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define all source files
file(GLOB_RECURSE URANIUM_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Create static library from the source files
add_library(uranium_static STATIC ${URANIUM_SOURCES})

# Include directories for the target
target_include_directories(uranium_static 
  PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link additional libraries
target_link_libraries(uranium_static
  ${GLFW_STATIC_LIB}
  ${VULKAN_STATIC_LIB}
)