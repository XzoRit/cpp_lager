cmake_minimum_required(VERSION 3.12)

project(lib VERSION 0.0 DESCRIPTION "enter description here")

add_library(lib_obj OBJECT)
target_sources(lib_obj PRIVATE "lib.cpp")
target_include_directories(lib_obj PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_library(lib)
target_link_libraries(lib PUBLIC lib_obj)

add_library(lib::lib ALIAS lib)

add_executable(lib_test)
target_sources(
  lib_test
  PRIVATE
  "lib.test.cpp"
  "main.test.cpp"
)
target_link_libraries(lib_test PRIVATE lib::lib Boost::unit_test_framework)

add_test(NAME lib::test COMMAND lib_test "--color_output=false")
