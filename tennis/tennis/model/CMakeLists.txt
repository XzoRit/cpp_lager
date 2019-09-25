cmake_minimum_required(VERSION 3.12)

add_library(
  model_obj
  OBJECT
)

target_sources(
  model_obj
  PRIVATE
    "model.cpp"
)

target_include_directories(
  model_obj
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/../.."
)

target_compile_features(
  model_obj
  PUBLIC
    cxx_std_17
)

add_library(
  model
)

target_link_libraries(
  model
  PUBLIC
    model_obj
)

add_library(
  tennis::model
  ALIAS model
)

add_executable(
  model_test
)

target_sources(
  model_test
  PRIVATE
    "model.test.cpp"
    "main.test.cpp"
)

target_link_libraries(
  model_test
  PRIVATE
    tennis::model
    Boost::unit_test_framework
)

add_test(
  NAME
    model::test
  COMMAND
    model_test
    "--color_output=false"
)
