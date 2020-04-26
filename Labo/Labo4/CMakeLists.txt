cmake_minimum_required(VERSION 3.16)
project(Labo4)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

file(GLOB DATA data/isbn/* data/quiz/* data/synoniemen/* data/warmste-week/* data/yahtzee/*)

add_executable(Labo4
        src/hashfunctions.h
        src/main.cpp)

add_custom_command(TARGET Labo4 PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/data/ ${CMAKE_BINARY_DIR}/data/
        )