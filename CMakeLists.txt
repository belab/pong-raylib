cmake_minimum_required(VERSION 3.5.0)
project(pong-raylib VERSION 0.1.0 LANGUAGES C CXX)

find_package(raylib CONFIG REQUIRED)

add_executable(pong-raylib main.cpp)
target_link_libraries(pong-raylib PRIVATE raylib)

