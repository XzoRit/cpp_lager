add_executable(
  counter_console_exe
)

target_sources(
  counter_console_exe
  PRIVATE
  "main.cpp"
)

target_compile_features(
  counter_console_exe
  PRIVATE
  cxx_std_17
)

target_link_libraries(
  counter_console_exe
  PRIVATE
    counter::model
    counter::console_view
    Boost::program_options
    lager
)

add_test(
  NAME
    counter::console_exe
  COMMAND
    counter_console_exe
    "--help"
)
