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

add_executable(
  tennis_imgui_app_exe
)

target_sources(
  tennis_imgui_app_exe
  PRIVATE
    "imgui_app.cpp"
)

target_compile_features(
  tennis_imgui_app_exe
  PRIVATE
    cxx_std_17
)

find_package(
  OpenGL
  REQUIRED
)

find_package(
  SDL2
  REQUIRED
)

include_directories(
  ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(
  tennis_imgui_app_exe
  PRIVATE
    tennis::imgui_view
    imgui
    lager
    OpenGL::GL
    ${SDL2_LIBRARIES}
)

add_test(
  NAME
    tennis::imgui_exe
  COMMAND
    tennis_imgui_app_exe
)
