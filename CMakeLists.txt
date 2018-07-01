cmake_minimum_required(VERSION 3.10)
project(LOOP C)

set(CMAKE_C_STANDARD 99)

add_executable(LOOP main.c interpreter.c parser.c executor.c interpreter.h parser.h executor.h)