cmake_minimum_required(VERSION 3.5.0)
project(pong-raylib VERSION 0.1.0 LANGUAGES C CXX)

find_package(raylib CONFIG REQUIRED)

add_executable(pong-raylib main.cpp)

target_compile_options(pong-raylib PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/W3 /permissive- /TP>
    $<$<CXX_COMPILER_ID:GNU>:-Wall -Wextra>)

target_link_libraries(pong-raylib PRIVATE raylib)

