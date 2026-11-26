cmake_minimum_required(VERSION 3.20)
project(pulsicon LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(
    glfw 
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG        3.5.1 
)

FetchContent_MakeAvailable(catch)

set(SOURCE
src/main.cpp)
add_executable(pulsicon ${SOURCE})

target_link_libraries(pulsicon PRIVATE glfw)
