set(
  inc_dir
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
  src_dir
  ${inc_dir}/counter/view/gui/console
)

add_library(
  counter_gui_console
)

target_sources(
  counter_gui_console
  PRIVATE
    "${src_dir}/console.cpp"
    "${src_dir}/console.hpp"
)

target_compile_features(
  counter_gui_console
  PUBLIC
    cxx_std_17
)

target_include_directories(
  counter_gui_console
  PUBLIC
    ${inc_dir}
)

target_link_libraries(
  counter_gui_console
  PRIVATE
    counter::view::model
    Boost::program_options
)

add_library(
  counter::gui::console
  ALIAS
  counter_gui_console
)
