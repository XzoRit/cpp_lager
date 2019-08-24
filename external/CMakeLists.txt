add_subdirectory(boost)

add_library(lager INTERFACE)
target_include_directories(lager INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/lager")
target_compile_features(lager INTERFACE cxx_std_17)
