
cmake_minimum_required(VERSION 3.16)
project(HelloWorld)

add_executable(main main.c)

find_package(SDL3 REQUIRED)

target_link_libraries(main PRIVATE SDL3::SDL3)
