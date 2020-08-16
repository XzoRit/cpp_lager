add_executable(
  tennis_imgui_app_exe
)

target_sources(
  tennis_imgui_app_exe
  PRIVATE
  "main.cpp"
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
