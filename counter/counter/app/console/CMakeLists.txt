add_executable(
  counter_exe_console
)

target_sources(
  counter_exe_console
  PRIVATE
    "main.cpp"
)

target_compile_features(
  counter_exe_console
  PRIVATE
    cxx_std_17
)

target_link_libraries(
  counter_exe_console
  PRIVATE
    counter::view::model
    counter::gui::console
    Boost::program_options
    lager
)

add_test(
  NAME
    counter::exe::console
  COMMAND
    counter_exe_console
    "--help"
)
