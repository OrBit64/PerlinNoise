cmake_minimum_required(VERSION 3.12)
project(PerlinNoise)

set(CMAKE_CXX_STANDARD 11)


# External libraries ----------------------------------------------------------
include(FetchContent)

# Raylib
# 4.5.0 - last version
set(RAYLIB_VERSION 6.0)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.zip
)

# target_include_directories(raylib PUBLIC ${raylib_SOURCE_DIR})

# FetchContent_Declare(
#     raylib
#     URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
#     FIND_PACKAGE_ARGS ${RAYLIB_VERSION} EXACT
# )
# set(BUILD_EXAMPLES OFF CACHE INTERNAL "")

# ImGui 
FetchContent_Declare(
    imgui
    URL https://github.com/ocornut/imgui/archive/refs/heads/master.zip
)
FetchContent_Declare(
    rlimgui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
    GIT_TAG main
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)
FetchContent_MakeAvailable(imgui rlimgui)

add_library(ImGui STATIC
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp
)
target_include_directories(ImGui PUBLIC ${imgui_SOURCE_DIR})
add_library(rlImGui STATIC
    ${rlimgui_SOURCE_DIR}/rlImGui.cpp
)
target_include_directories(rlImGui PUBLIC ${rlimgui_SOURCE_DIR})
target_link_libraries(rlImGui PUBLIC raylib ImGui)
# target_link_directories(rlImGui PUBLIC raylib ImGui)

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
    ImGui
    rlImGui
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