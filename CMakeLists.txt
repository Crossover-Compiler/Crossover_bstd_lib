cmake_minimum_required(VERSION 3.24)
project(Crossover_bstd_lib C)


set(CMAKE_C_STANDARD 11)

add_library(Crossover_bstd_lib include/arithmetic.h include/number.h include/numutils.h include/picture.h include/picutils.h src/arithmetic.c src/numutils.c src/picutils.c)

add_executable(main test/main.c include/arithmetic.h include/number.h include/numutils.h include/picture.h include/picutils.h src/arithmetic.c src/numutils.c src/picutils.c)

target_link_libraries(main m)