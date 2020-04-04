set(
  inc_dir
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
  src_dir
  ${inc_dir}/counter/view/model
)

add_library(
  counter_view_model
)

target_sources(
  counter_view_model
  PRIVATE
    "${src_dir}/model.cpp"
    "${src_dir}/model.hpp"
)

target_compile_features(
  counter_view_model
  PUBLIC
    cxx_std_17
)

target_include_directories(
  counter_view_model
  PUBLIC
    ${inc_dir}
)

target_link_libraries(
  counter_view_model
  PUBLIC
    counter::model
)

add_library(
  counter::view::model
  ALIAS
    counter_view_model
)
