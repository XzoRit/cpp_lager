add_executable(
  tennis_console_app_exe
)

target_sources(
  tennis_console_app_exe
  PRIVATE
    "console_app.cpp"
)

target_compile_features(
  tennis_console_app_exe
  PRIVATE
    cxx_std_17
)

target_link_libraries(
  tennis_console_app_exe
  PRIVATE
    tennis::model
    tennis::console_view
    Boost::program_options
    lager
)

add_test(
  NAME
    tennis::console_exe
  COMMAND
    tennis_console_app_exe "--help"
)
