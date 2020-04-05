set(
  inc_dir
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
  src_dir
  ${inc_dir}/counter/model
)

add_library(
  counter_model
)

target_sources(
  counter_model
  PRIVATE
    "${src_dir}/model.cpp"
    "${src_dir}/model.hpp"
)

target_compile_features(
  counter_model
  PUBLIC
    cxx_std_17
)

target_include_directories(
  counter_model
  PUBLIC
    ${inc_dir}
)

add_library(
  counter::model
  ALIAS
    counter_model
)

add_executable(
  counter_model_test
)

target_sources(
  counter_model_test
  PRIVATE
    "${src_dir}/model.test.cpp"
    "${src_dir}/main.test.cpp"
)

target_link_libraries(
  counter_model_test
  PRIVATE
    counter::model
    Boost::unit_test_framework
)

add_test(
  NAME
    counter::model_test
  COMMAND
    counter_model_test
    "--color_output=false"
)
