cmake_minimum_required(VERSION 3.0.0)

project(satellite VERSION 0.1.0 LANGUAGES C)

add_executable(satellite_tcc ${PROJECT_SOURCE_DIR}/src/tccmain.c)

add_executable(satellite_leo ${PROJECT_SOURCE_DIR}/src/leomain.c)

add_executable(satellite_geo ${PROJECT_SOURCE_DIR}/src/geomain.c)

# aux_source_directory(${PROJECT_SOURCE_DIR}/src/utlis utlis_src)

# file(GLOB_RECURSE utlis_header CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/src/utlis/header/*.h)

set(src_casmsg 
    ${PROJECT_SOURCE_DIR}/src/utlis/header/casmsg.h
    ${PROJECT_SOURCE_DIR}/src/utlis/casmsg.c
)

target_sources(satellite_tcc PUBLIC 
    ${PROJECT_SOURCE_DIR}/src/utlis/header/tcc.h
    ${PROJECT_SOURCE_DIR}/src/utlis/tcc.c

    ${src_casmsg}
)

target_sources(satellite_leo PUBLIC 
    ${PROJECT_SOURCE_DIR}/src/utlis/header/leo.h
    ${PROJECT_SOURCE_DIR}/src/utlis/leo.c

    ${src_casmsg}
)

target_sources(satellite_geo PUBLIC 
    ${PROJECT_SOURCE_DIR}/src/utlis/header/geo.h
    ${PROJECT_SOURCE_DIR}/src/utlis/geo.c

    ${src_casmsg}
)