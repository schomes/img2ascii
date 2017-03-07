cmake_minimum_required(VERSION 3.1.2)
project(img2ascii)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(img2ascii ${SOURCES})