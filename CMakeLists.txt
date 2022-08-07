cmake_minimum_required(VERSION 3.0.0)
project(tetris VERSION 0.1.0)

aux_source_directory(src MAIN_SRC)


add_executable(tetris ${MAIN_SRC})
add_executable(ttest ./test/test.cpp)
