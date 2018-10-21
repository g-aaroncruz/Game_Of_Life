cmake_minimum_required (VERSION 2.6)
project (game_of_life)

set(CMAKE_BUILD_TYPE Debug)

find_package(X11 REQUIRED)

message(STATUS "X11 Include Path :: ${X11_INCLUDE_DIR}")

include_directories("include" ${X11_INCLUDE_DIR})


add_executable(game_of_life
    src/main.cpp
    src/board.cpp
)

target_link_libraries (game_of_life
    pthread
    ${X11_LIBRARIES}
)
