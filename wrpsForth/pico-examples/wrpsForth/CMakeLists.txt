# Thu 31 Mar 18:18:41 UTC 2022

add_executable(wrpsForth
        wrpsForth.c
        )

target_compile_definitions(wrpsForth PRIVATE
    # enable this flag only for no_flash compile:
    # NO_FLASH_CMAKE=-1
    # NO_FLASH_CMAKE=-1
)

target_link_libraries(wrpsForth PRIVATE forth ws2812 hardware_flash pico_stdlib)

# pico_set_binary_type(wrpsForth no_flash)
pico_set_binary_type(wrpsForth copy_to_ram)

pico_enable_stdio_usb(wrpsForth 1)
pico_enable_stdio_uart(wrpsForth 1) # was zero

pico_add_extra_outputs(wrpsForth)

example_auto_set_url(wrpsForth)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

add_subdirectory(forth)
add_subdirectory(pio)
