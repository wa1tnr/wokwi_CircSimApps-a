# Wed 30 Mar 20:44:06 UTC 2022

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

# target_link_libraries(forth hardware_watchdog pico_stdlib)

# latest:
# target_link_libraries(forth pico_runtime flash pico_stdlib)

include_directories(../include)
add_library(forth forth.c)
target_link_libraries(forth pico_runtime hardware_flash pico_stdlib)
