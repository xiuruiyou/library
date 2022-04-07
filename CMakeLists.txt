cmake_minimum_required(VERSION 3.21)
project(CWK1 C)

set(CMAKE_C_STANDARD 99)

add_executable(CWK1 main.c)
add_executable(option option.c option.h)
add_executable(user user.c user.h)
add_executable(do_book do_book.c do_book.h)