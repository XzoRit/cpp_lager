cmake_minimum_required(VERSION 3.10)

project(app VERSION 0.0)

enable_testing()
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(app)
add_subdirectory(lib)
add_subdirectory(external)
