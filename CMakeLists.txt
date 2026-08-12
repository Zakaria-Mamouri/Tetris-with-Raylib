cmake_minimum_required(VERSION 3.15)
project(Tetris LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Fetch raylib automatically (no manual install needed) ---
include(FetchContent)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.0
)
# Don't build raylib's examples/games, just the library
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# --- Project sources ---
file(GLOB SOURCES "src/*.cpp")

add_executable(Tetris ${SOURCES})

target_include_directories(Tetris PRIVATE include)
target_link_libraries(Tetris PRIVATE raylib)

# Windows-specific system libs raylib needs when statically linked
if (WIN32)
    target_link_libraries(Tetris PRIVATE winmm gdi32 opengl32)
endif()
