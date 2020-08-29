set(
  inc_dir
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
  src_dir
  ${inc_dir}/tennis/view/gui/imgui
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
  PRIVATE
    imgui
)

add_library(
  tennis::imgui_view
  ALIAS
  tennis_imgui_view
)

add_executable(
  tennis_imgui_view_test
)

target_sources(
  tennis_imgui_view_test
  PRIVATE
  "${src_dir}/imgui.test.cpp"
  "${src_dir}/main.test.cpp"
)

target_link_libraries(
  tennis_imgui_view_test
  PRIVATE
    tennis::imgui_view
    Boost::unit_test_framework
)

add_test(
  NAME
    tennis::imgui_view_test
  COMMAND
    tennis_imgui_view_test
    "--color_output=false"
)
