set(
  inc_dir
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
  src_dir
  ${inc_dir}/counter/view
)

add_library(
  counter_console_view
)

target_sources(
  counter_console_view
  PRIVATE
  "${src_dir}/console.cpp"
  "${src_dir}/console.hpp"
)

target_compile_features(
  counter_console_view
  PUBLIC
  cxx_std_17
)

target_include_directories(
  counter_console_view
  PUBLIC
    ${inc_dir}
)

target_link_libraries(
  counter_console_view
  PUBLIC
    counter::model
    Boost::program_options
)

add_library(
  counter::console_view
  ALIAS
  counter_console_view
)

add_library(
  counter_imgui_view
)

target_sources(
  counter_imgui_view
  PRIVATE
  "${src_dir}/imgui.cpp"
  "${src_dir}/imgui.hpp"
)

target_compile_features(
  counter_imgui_view
  PUBLIC
  cxx_std_17
)

target_include_directories(
  counter_imgui_view
  PUBLIC
    ${inc_dir}
)

target_link_libraries(
  counter_imgui_view
  PUBLIC
    imgui
)

add_library(
  counter::imgui_view
  ALIAS
  counter_imgui_view
)
