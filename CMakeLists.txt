cmake_minimum_required(VERSION 3.12)
project(pqxx-async)

add_custom_target(felspar-check)
set_property(TARGET felspar-check PROPERTY EXCLUDE_FROM_ALL TRUE)
add_custom_target(felspar-examples)
add_custom_target(felspar-stress)
set_property(TARGET felspar-stress PROPERTY EXCLUDE_FROM_ALL TRUE)

add_subdirectory(libs)
target_compile_features(pqxx PUBLIC cxx_std_20)
add_subdirectory(examples)
