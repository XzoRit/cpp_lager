set(
  inc_dir
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
  src_dir
  ${inc_dir}/tennis/view
)

add_library(
  console_view
)

target_sources(
  console_view
  PRIVATE
  "${src_dir}/console.cpp"
  "${src_dir}/console.hpp"
)

target_compile_features(
  console_view
  PUBLIC
  cxx_std_17
)

target_include_directories(
  console_view
  PUBLIC
  ${inc_dir}
)

target_link_libraries(
  console_view
  PUBLIC
    tennis::model
    Boost::program_options
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
  "${src_dir}/console.test.cpp"
  "${src_dir}/main.test.cpp"
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

add_library(
  imgui_view
)

target_sources(
  imgui_view
  PRIVATE
  "${src_dir}/imgui.cpp"
)

target_compile_features(
  imgui_view
  PUBLIC
  cxx_std_17
)

target_include_directories(
  imgui_view
  PUBLIC
  ${inc_dir}
)

target_link_libraries(
  imgui_view
  PUBLIC
  imgui
)

add_library(
  tennis::imgui_view
  ALIAS imgui_view
)
