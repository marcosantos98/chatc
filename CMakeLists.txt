cmake_minimum_required(VERSION 3.20)

project(chatc C)

find_package(raylib 4.0.0 QUIET)
if (NOT raylib_FOUND)
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/4.0.0.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

set(CMAKE_C_COMPILER "cc")
set(CMAKE_C_FLAGS "-std=c2x")

add_executable(server server.c)
add_executable(client raygui.h client.h client_gui.c)

target_link_libraries(client raylib m)