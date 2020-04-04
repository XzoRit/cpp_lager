find_package(
  SDL2
  REQUIRED
)

include_directories(
  ${SDL2_INCLUDE_DIRS}
)

add_executable(
  counter_exe_imgui
)

target_sources(
  counter_exe_imgui
  PRIVATE
    "main.cpp"
)

target_compile_features(
  counter_exe_imgui
  PRIVATE
    cxx_std_17
)

target_link_libraries(
  counter_exe_imgui
  PRIVATE
    counter::view::model
    counter::gui::imgui
    lager
    imgui
    ${SDL2_LIBRARIES}
)

add_test(
  NAME
    counter::exe::imgui
  COMMAND
    counter_exe_imgui
)
