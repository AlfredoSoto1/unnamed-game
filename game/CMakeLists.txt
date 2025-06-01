# MyGame executable
project(mygame)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define all source files
file(GLOB_RECURSE MYGAME_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Create the game executable
add_executable(${CMAKE_PROJECT_NAME} ${MYGAME_SOURCES} ${GLAD_SRC})

# Include directories for the target
target_include_directories(${CMAKE_PROJECT_NAME} 
  PUBLIC  "${CMAKE_CURRENT_SOURCE_DIR}/include"
  PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link additional libraries
if(WIN32)
    target_link_libraries(${CMAKE_PROJECT_NAME}
        PRIVATE uranium_static
        PRIVATE ${GLFW_STATIC_LIB}
        PRIVATE ${VULKAN_STATIC_LIB}
        PRIVATE opengl32
        PRIVATE gdi32
        PRIVATE user32
        PRIVATE shell32
    )
elseif(UNIX)
    target_link_libraries(${CMAKE_PROJECT_NAME}
        PRIVATE uranium_static
        PRIVATE ${GLFW_STATIC_LIB}
        PRIVATE ${VULKAN_STATIC_LIB}
        PRIVATE GL
        PRIVATE X11
        PRIVATE pthread
        PRIVATE dl
        PRIVATE m
    )
endif()