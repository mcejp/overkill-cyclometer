   
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
    # Alpha pre-multiply trick from https://legacy.imagemagick.org/discourse-server/viewtopic.php?p=98820&sid=43feb8dfb6e1458e62baec394189bb96#p98820
    add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated_include/${FONT}.h
            COMMAND convert ${CMAKE_CURRENT_LIST_DIR}/assets/fonts/${FONT}.png \\\( +clone -alpha Extract \\\) -channel RGB -compose Multiply -composite -white-threshold 50% -colorspace gray -depth 1 r:- | xxd -i > ${CMAKE_CURRENT_BINARY_DIR}/generated_include/${FONT}.h
            MAIN_DEPENDENCY ${CMAKE_CURRENT_LIST_DIR}/assets/fonts/${FONT}.png)

    list(APPEND GENERATED_FONT_HEADERS ${CMAKE_CURRENT_BINARY_DIR}/generated_include/${FONT}.h)
endforeach()

add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated_include/splash.h
        COMMAND convert ${CMAKE_CURRENT_LIST_DIR}/assets/splash.png \\\( +clone -alpha Extract \\\) -channel RGB -compose Multiply -composite -negate -white-threshold 50% -colorspace gray -depth 1 r:- | xxd -i > ${CMAKE_CURRENT_BINARY_DIR}/generated_include/splash.h
        MAIN_DEPENDENCY ${CMAKE_CURRENT_LIST_DIR}/assets/splash.png)

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
            ${CMAKE_CURRENT_BINARY_DIR}/generated_include/splash.h

            # devprop stuff
            generated/devprop_bikECU.c
            generated/devprop_bikECU.h
            devprop/cobs.c
            devprop/cobs.h
            devprop/devprop_can_ext_v1.c
            devprop/devprop_can_ext_v1.h
            devprop/devprop.h
            devprop.cpp
            devprop.hpp
            )

    target_link_libraries(bikECU
            hardware_adc
            hardware_flash
            hardware_i2c
            pico_bootsel_via_double_reset
            pico_stdlib
            )

    pico_enable_stdio_usb(bikECU 1)
    add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

    # create map/bin/hex file etc.
    pico_add_extra_outputs(bikECU)

    target_include_directories(bikECU PRIVATE
            devprop
            generated
            ${CMAKE_CURRENT_BINARY_DIR}/generated_include
            )
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
            ${CMAKE_CURRENT_BINARY_DIR}/generated_include/splash.h
            )

    target_include_directories(bikECU_libretro PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/generated_include)
endif()
