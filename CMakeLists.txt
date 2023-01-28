cmake_minimum_required(VERSION 3.10)
project(Arcade)

add_subdirectory(Snake)

add_executable(Arcade main.cpp Chooser.cpp Pairs.cpp)
target_link_libraries(Arcade ncursesw)
target_link_libraries(Arcade Snake)
