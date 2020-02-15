set(
  inc_dir
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
  src_dir
  ${inc_dir}/tennis/model
)

add_library(
  tennis_model
)

target_sources(
  tennis_model
  PRIVATE
  "${src_dir}/model.cpp"
  "${src_dir}/model.hpp"
)

target_compile_features(
  tennis_model
  PUBLIC
  cxx_std_17
)

target_include_directories(
  tennis_model
  PUBLIC
  ${inc_dir}
)

target_link_libraries(
  tennis_model
  PUBLIC
  lager
)

add_library(
  tennis::model
  ALIAS tennis_model
)

add_executable(
  tennis_model_test
)

target_sources(
  tennis_model_test
  PRIVATE
  "${src_dir}/model.test.cpp"
  "${src_dir}/main.test.cpp"
)

target_link_libraries(
  tennis_model_test
  PRIVATE
    tennis::model
    Boost::unit_test_framework
)

add_test(
  NAME
    tennis::model_test
  COMMAND
    tennis_model_test
    "--color_output=false"
)
