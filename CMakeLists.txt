cmake_minimum_required(VERSION 3.20)

project(chatc C)

set(CMAKE_C_COMPILER "cc")
set(CMAKE_C_FLAGS "-Wall -Wextra -std=c99 -pedantic")

add_executable(server main.c)
add_executable(client client.c)

target_link_libraries(client raylib)