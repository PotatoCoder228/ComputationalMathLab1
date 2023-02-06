cmake_minimum_required(VERSION 3.25)
project(CountMathLab1 C)

set(CMAKE_C_STANDARD 11)

add_executable(CountMathLab1 src/main.c src/utils/printer.c include/utils/printer.h src/app.c include/app.h src/io/io_handler.c include/io/io_handler.h)
