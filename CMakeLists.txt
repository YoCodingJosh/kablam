cmake_minimum_required(VERSION 3.16)
project(Kablam VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS OFF)

if (UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

set (APP_FULL_NAME "Kablam")
string(TIMESTAMP COPYRIGHT_YEAR "%Y")

find_package(SDL2 REQUIRED COMPONENTS SDL2)
find_package(SDL2_ttf CONFIG REQUIRED)

add_executable(Kablam "")

target_sources(Kablam
    PRIVATE
        ./FPSLimiter.cpp
        ./Assets.cpp
        ./Menu.cpp
        ./Game.cpp
        ./Main.cpp
)

target_link_libraries(Kablam PRIVATE SDL2::SDL2 SDL2::SDL2main SDL2_ttf::SDL2_ttf)

file(COPY assets/ DESTINATION assets/)
