cmake_minimum_required(VERSION 3.12)
project(PerlinNoise)

set(CMAKE_CXX_STANDARD 11)


# External libraries ----------------------------------------------------------
include(FetchContent)

# Raylib
# 4.5.0 - last version
set(RAYLIB_VERSION 5.0)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.zip
)
FetchContent_MakeAvailable(raylib)

# FetchContent_Declare(
#     raylib
#     URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
#     FIND_PACKAGE_ARGS ${RAYLIB_VERSION} EXACT
# )
# set(BUILD_EXAMPLES OFF CACHE INTERNAL "")


# Our libs --------------------------------------------------------------------
# Our math lib
add_library(PerlinMath 
    src/perlin_math.cpp
    includes/perlin_math.h
)
target_include_directories(PerlinMath PUBLIC includes/)

# UI lib
add_library(PerlinUI
    src/window.cpp
    includes/window.h
)
target_include_directories(PerlinUI PUBLIC includes/)
target_link_libraries(PerlinUI 
    raylib
    PerlinMath
)


# Project ---------------------------------------------------------------------
add_executable(${PROJECT_NAME}
    src/main.cpp    
)
target_link_libraries(${PROJECT_NAME}
    # PerlinMath
    PerlinUI
)


# Some stuff for crossplatform ------------------------------------------------
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()