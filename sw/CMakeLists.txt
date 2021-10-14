   
cmake_minimum_required(VERSION 3.12)

if (PICO_SDK_PATH)
    # Pull in SDK (must be before project)
    include(pico_sdk_import.cmake)
endif()

project(bikECU C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated_include)

# Generate font headers
set(GENERATED_FONT_HEADERS)

foreach(FONT curses_vector_8x12 curses_vector_32x48 Shizzle_1280x500)
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated_include/${FONT}.h
            COMMAND convert ${CMAKE_CURRENT_LIST_DIR}/assets/fonts/${FONT}.png -colorspace gray -depth 1 r:- | xxd -i > ${CMAKE_CURRENT_BINARY_DIR}/generated_include/${FONT}.h
            MAIN_DEPENDENCY ${CMAKE_CURRENT_LIST_DIR}/assets/fonts/${FONT}.png)

    list(APPEND GENERATED_FONT_HEADERS ${CMAKE_CURRENT_BINARY_DIR}/generated_include/${FONT}.h)
endforeach()

if (PICO_SDK_PATH)
    # Initialize the SDK
    pico_sdk_init()

    add_executable(bikECU
            app.cpp
            draw.cpp
            draw.hpp
            main.cpp
            SeeedGrayOLED.cpp
            SeeedGrayOLED.h
            storage.cpp
            storage.hpp
            ${GENERATED_FONT_HEADERS}
            )

    target_link_libraries(bikECU
            hardware_adc
            hardware_flash
            hardware_i2c
            pico_stdlib
            )

    pico_enable_stdio_usb(bikECU 1)

    # create map/bin/hex file etc.
    pico_add_extra_outputs(bikECU)

    target_include_directories(bikECU PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated_include)
else()
    add_library(bikECU_libretro SHARED
            app.cpp
            app.hpp
            draw.cpp
            draw.hpp
            libretro.h
            libretro_main.cpp
            storage.cpp
            storage.hpp
            ${GENERATED_FONT_HEADERS}
            )

    target_include_directories(bikECU_libretro PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated_include)
endif()