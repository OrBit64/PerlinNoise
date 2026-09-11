cmake_minimum_required(VERSION 3.12)
project(PerlinNoise)

set(CMAKE_CXX_STANDARD 11)

# Raylib
include(FetchContent)

set(RAYLIB_VERSION 4.5.0)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    FIND_PACKAGE_ARGS ${RAYLIB_VERSION} EXACT
)
set(BUILD_EXAMPLES OFF CACHE INTERNAL "")
FetchContent_MakeAvailable(raylib)

# Project
add_executable(${PROJECT_NAME}
    src/main.cpp    
)
target_link_libraries(${PROJECT_NAME}
    raylib
)

# Some stuff for crossplatform
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()