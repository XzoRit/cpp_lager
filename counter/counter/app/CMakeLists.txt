add_executable(
  counter_console_exe
)

target_sources(
  counter_console_exe
  PRIVATE
  "console_app.cpp"
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

add_executable(
  counter_imgui_app_exe
)

target_sources(
  counter_imgui_app_exe
  PRIVATE
  "imgui_app.cpp"
)

target_compile_features(
  counter_imgui_app_exe
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
  counter_imgui_app_exe
  PRIVATE
    imgui
    lager
    OpenGL::GL
    ${SDL2_LIBRARIES}
)

add_test(
  NAME
    counter::imgui_exe
  COMMAND
    counter_imgui_app_exe
)
