cmake_minimum_required(VERSION 3.24)

project(SpotifyC VERSION 0.1.0 LANGUAGES C)
SET(PROJECT_TARGET_EXE TestExecutable)
SET(PROJECT_TARGET_LIB SpotifyCLib)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(configured)