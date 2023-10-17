project(password-game)
cmake_minimum_required(VERSION 3.24)

add_executable(game main.cpp)
target_include_directories(game PRIVATE .)
