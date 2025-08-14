cmake_minimum_required(VERSION 3.13)

project(pmodoro LANGUAGES C)

if (NOT MSVC)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "5.5"
)

FetchContent_MakeAvailable(raylib)

add_executable(
    pmodoro

    src/buttons.c
    src/buttons.h
    src/constants.h
    src/main.c
    src/time.c
    src/time.h
    src/vector-math.h
)

target_link_libraries(pmodoro PRIVATE raylib)
