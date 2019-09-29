cmake_minimum_required(VERSION 3.12)

add_library(
  console_view_obj
  OBJECT
)

target_sources(
  console_view_obj
  PRIVATE
    "console.cpp"
)

target_include_directories(
  console_view_obj
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../.."
)

target_link_libraries(
  console_view_obj
  PUBLIC
    tennis::model
    Boost::program_options
)

target_compile_features(
  console_view_obj
  PUBLIC
    cxx_std_17
)

add_library(
  console_view
)

target_link_libraries(
  console_view
  PUBLIC
    console_view_obj
)

add_library(
  tennis::console_view
  ALIAS console_view
)

add_executable(
  console_view_test
)

target_sources(
  console_view_test
  PRIVATE
    "console.test.cpp"
    "main.test.cpp"
)

target_link_libraries(
  console_view_test
  PRIVATE
    tennis::console_view
    Boost::unit_test_framework
)

add_test(
  NAME
    console_view::test
  COMMAND
    console_view_test
    "--color_output=false"
)
