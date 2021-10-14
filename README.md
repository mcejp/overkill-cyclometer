# Overkill Cyclocomputer

## Compile it

### For Pi Pico

Prerequisites:
- Raspberry Pi Pico SDK
- Recent arm-none-eabi-gcc toolchain
- ImageMagick (`convert` tool) & xxd

```
mkdir build
cd build
env PICO_SDK_PATH=... PICO_TOOLCHAIN_PATH=... cmake ..
make

# flash
cp bikECU.uf2 /media/RPI-RP2/
```

### For PC (Simulation)

Prerequisites:
- C++20 compiler
- Libretro frontent ([SDLArch](https://github.com/heuripedes/sdlarch) / [RetroArch](https://www.retroarch.com/))
- ImageMagick (`convert` tool) & xxd

```
mkdir build_libretro
cd build_libretro
cmake ..
make
sdlarch ./libbikECU_libretro.so
# alternatively:
# retroarch -L ./libbikECU_libretro.so
```

## Credits

- curses_vector fonts: http://www.bay12forums.com/smf/index.php?topic=161328.0
- libretro: Copyright (C) 2010-2020 The RetroArch team
- [SeeedGrayOLED library](https://github.com/Seeed-Studio/OLED_Display_96X96): Copyright (c) 2011 seeed technology inc.

## BOM

TBD
