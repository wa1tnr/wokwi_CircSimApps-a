# Thu 31 Mar 18:18:41 UTC 2022

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

include_directories(../include)
include_directories(../gforth)
add_library(forth forth.c)
target_link_libraries(forth pico_runtime hardware_flash pico_stdlib)
