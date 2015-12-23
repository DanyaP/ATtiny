cmake_minimum_required(VERSION 3.1)
project(Attiny)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(HEADERS attiny.h instractions.h)
set(SOURCE_FILES main.cpp attiny.cpp instractions.cpp)

add_executable(Attiny ${SOURCE_FILES} ${HEADERS} doing_instractions.h doing_instractions.cpp)