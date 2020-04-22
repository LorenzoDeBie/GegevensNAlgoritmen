cmake_minimum_required(VERSION 3.15)
project(Labo3)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

file(GLOB DATA "src/*.txt")
file(GLOB SUDOKUS "src/sudokus/*")

file(COPY ${DATA} DESTINATION "src/")

file(COPY ${SUDOKUS} DESTINATION "src/sudokus/")

add_executable(Labo3 ${SOURCES})