set(
  inc_dir
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
  src_dir
  ${inc_dir}/counter/view/gui/imgui
)

add_library(
  counter_gui_imgui
)

target_sources(
  counter_gui_imgui
  PRIVATE
    "${src_dir}/imgui.cpp"
    "${src_dir}/imgui.hpp"
)

target_compile_features(
  counter_gui_imgui
  PUBLIC
    cxx_std_17
)

target_include_directories(
  counter_gui_imgui
  PUBLIC
    ${inc_dir}
)

target_link_libraries(
  counter_gui_imgui
  PUBLIC
   counter::view::model
   lager
  PRIVATE
   imgui
)

add_library(
  counter::gui::imgui
  ALIAS
  counter_gui_imgui
)
