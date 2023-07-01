cmake_minimum_required(VERSION 3.22)
project(Crossover_bstd_lib LANGUAGES C VERSION 0.1 DESCRIPTION "BSTD: The BabyCobol Standard Library")

set(CMAKE_C_STANDARD 11)

include(GNUInstallDirs)

add_library(bstd SHARED
        src/arithmetic.c
        src/numutils.c
        src/picutils.c)

set_target_properties(bstd PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 0.1
        PUBLIC_HEADER "include/number.h;include/picture.h;include/numutils.h;include/picutils.h;include/arithmetic.h")

configure_file(bstd.pc.in bstd.pc @ONLY)

target_include_directories(bstd PRIVATE include)
target_include_directories(bstd PRIVATE src)

install(TARGETS bstd
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/bstd)

install(FILES ${CMAKE_BINARY_DIR}/bstd.pc
        DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)