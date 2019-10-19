add_subdirectory(boost)

add_library(
  lager
  INTERFACE
)

target_include_directories(
  lager
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/lager"
)

target_compile_features(
  lager
  INTERFACE
    cxx_std_17
)

add_library(
  imgui
)

target_sources(
  imgui
  PRIVATE
  "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_demo.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_draw.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/imgui/imgui_widgets.cpp"
)

target_include_directories(
  imgui
  PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/imgui"
)

target_compile_features(
  imgui
  PRIVATE
    cxx_std_17
)
