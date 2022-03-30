add_executable(sandbox-d
        sandbox-d.c
        )

# Sat Feb 27 23:45:07 UTC 2021

target_compile_definitions(sandbox-d PRIVATE
    # enable this flag only for no_flash compile:
    # NO_FLASH_CMAKE=-1
    # NO_FLASH_CMAKE=-1
)

# 11 May 00:40z trying PRIVATE on line below first time ever
target_link_libraries(sandbox-d PRIVATE forth pico-LED ws2812 hardware_flash pico_stdlib)

# pico_set_binary_type(sandbox-d copy_to_ram)
pico_set_binary_type(sandbox-d copy_to_ram)
# pico_set_binary_type(sandbox-d no_flash)
# pico_set_binary_type(sandbox-d no_flash)

pico_enable_stdio_usb(sandbox-d 1)
pico_enable_stdio_uart(sandbox-d 1) # was zero

pico_add_extra_outputs(sandbox-d)

example_auto_set_url(sandbox-d)

if ( CMAKE_COMPILER_IS_GNUCC )
    set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif()

add_subdirectory(forth)
# add_subdirectory(pico-hw)
add_subdirectory(pio)
