#include "draw.hpp"

#include <stdint.h>
#include <stdlib.h>

struct Font {
    uint8_t const* data;
    int char_w;
    int char_h;
    int stride;
};

// 144x256
//#include "09x16_lfl9x16B_Peter-Karrer.h"
//static Font karrer = {__09x16_lfl9x16B_Peter_Karrer_raw, 9, 16, 144/8};

//
static const uint8_t Shizzle_1280x500_bitmap[] = {
#include "Shizzle_1280x500.h"
};
const Font font16x20 = {Shizzle_1280x500_bitmap, 16, 20, 256 / 8};

// from http://www.bay12forums.com/smf/index.php?topic=161328.0
static const uint8_t curses_vector_8x12_bitmap[] = {
#include "curses_vector_8x12.h"
};
const Font font8x12 = {curses_vector_8x12_bitmap, 8, 12, 128 / 8};
static const uint8_t curses_vector_32x48_bitmap[] = {
#include "curses_vector_32x48.h"
};
const Font font32x48 = {curses_vector_32x48_bitmap, 32, 48, 512 / 8};

extern const uint8_t splash_bitmap[] = {
#include "splash.h"
};

void platformSendCommand(unsigned char command);
void platformSendData(unsigned char data);

#ifdef PICO_BUILD
void setTextXY(unsigned char Row, unsigned char Column) {
    platformSendCommand(0xb0 + (Row & 0x0F)); // set page/row
    platformSendCommand(0x10 + ((Column >> 4) & 0x07)); // set column high 3 byte
    platformSendCommand(Column & 0x0F);  // set column low 4 byte
}
#else
void setTextXY(unsigned char Row, unsigned char Column);
#endif


// https://stackoverflow.com/a/2602885
unsigned char reverse(unsigned char b) {
    b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
    b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
    b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
    return b;
}

void putChar(Font const& fnt, unsigned char C, int x_div_8, int y) {
    const int CHARS_PER_ROW_IN_FONT = 16;
    int row_in_font = C / CHARS_PER_ROW_IN_FONT * fnt.char_h;
    int col_in_font = C % CHARS_PER_ROW_IN_FONT * fnt.char_w;

    // algo: we need to transform character rows into 8-blocks to blit as columns
    // start at bottom-left
    for (int xx = 0; xx < (fnt.char_w + 7) / 8; xx++) {
        setTextXY(x_div_8 + xx, 127 - y - fnt.char_h);

        int keep_bits = fnt.char_w - xx * 8;
        int mask = (keep_bits < 8) ? (0xff00 >> keep_bits) : 0xff;

        // for every iteration, the OLED driver will automatically advance the cursor by 1 column (= up in real orientation)
        for (int yy = 0; yy < fnt.char_h; yy++) {
            int min_byte = (row_in_font + fnt.char_h - yy - 1) * fnt.stride + col_in_font / 8 + xx;
            int bit_offset = col_in_font % 8;

            int sample = fnt.data[min_byte] << bit_offset;

            if (bit_offset > 0) {
                sample |= fnt.data[min_byte + 1] >> (8 - bit_offset);
            }

            // TODO: optimize to not start a new i2c transaction for every single byte
            platformSendData(reverse(sample & mask));
        }
    }
}

void puttextat(Font const& font, int x_div_8, int y, const char* text) {
    for (size_t i = 0; text[i]; i++) {
        putChar(font, text[i], x_div_8, y);
        x_div_8 += (font.char_w + 7) / 8;
    }
}
