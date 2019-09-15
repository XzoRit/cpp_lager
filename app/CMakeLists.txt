cmake_minimum_required(VERSION 3.12)

project(app_executeable VERSION 0.0 DESCRIPTION "example app for usage of the lager lib")

add_executable(app_exe)
target_sources(app_exe PRIVATE "main.cpp")
target_compile_features(app_exe PRIVATE cxx_std_17)
target_link_libraries(app_exe PRIVATE lib::lib Boost::program_options)

add_test(NAME app::exe COMMAND app_exe "--help")
