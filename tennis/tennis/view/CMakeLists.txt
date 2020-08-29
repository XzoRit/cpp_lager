set(
  inc_dir
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
  src_dir
  ${inc_dir}/tennis/view
)

add_library(
  tennis_imgui_view
)

target_sources(
  tennis_imgui_view
  PRIVATE
  "${src_dir}/imgui.cpp"
  "${src_dir}/imgui.hpp"
)

target_compile_features(
  tennis_imgui_view
  PUBLIC
  cxx_std_17
)

target_include_directories(
  tennis_imgui_view
  PUBLIC
    ${inc_dir}
)

target_link_libraries(
  tennis_imgui_view
  PUBLIC
    imgui
)

add_library(
  tennis::imgui_view
  ALIAS
  tennis_imgui_view
)
