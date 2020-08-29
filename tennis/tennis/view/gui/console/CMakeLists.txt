set(
  inc_dir
  ${CMAKE_CURRENT_SOURCE_DIR}
)

set(
  src_dir
  ${inc_dir}/tennis/view/gui/console
)

add_library(
  tennis_console_view
)

target_sources(
  tennis_console_view
  PRIVATE
  "${src_dir}/console.cpp"
  "${src_dir}/console.hpp"
)

target_compile_features(
  tennis_console_view
  PUBLIC
  cxx_std_17
)

target_include_directories(
  tennis_console_view
  PUBLIC
    ${inc_dir}
)

target_link_libraries(
  tennis_console_view
  PUBLIC
    tennis::model
    Boost::program_options
)

add_library(
  tennis::console_view
  ALIAS
  tennis_console_view
)

add_executable(
  tennis_console_view_test
)

target_sources(
  tennis_console_view_test
  PRIVATE
  "${src_dir}/console.test.cpp"
  "${src_dir}/main.test.cpp"
)

target_link_libraries(
  tennis_console_view_test
  PRIVATE
    tennis::console_view
    Boost::unit_test_framework
)

add_test(
  NAME
    tennis::console_view_test
  COMMAND
    tennis_console_view_test
    "--color_output=false"
)
