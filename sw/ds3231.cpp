#include "ds3231.hpp"

#include "hardware/i2c.h"

#define THE_I2C i2c0
#define THE_ADDRESS 0b1101000

namespace ds3231 {

constexpr inline int bcd_to_binary(uint8_t value) {
    return (value >> 4) * 10 + (value & 0x0f);
}

constexpr inline uint8_t binary_to_bcd(uint8_t value) {
    return ((value / 10) << 4) + (value % 10);
}

Registers read_registers() {
    // reset address
    uint8_t const frame[] { 0x00 };
    i2c_write_blocking(THE_I2C, THE_ADDRESS, frame, sizeof(frame), false);

    Registers regs_out;
    i2c_read_blocking(THE_I2C, THE_ADDRESS, (uint8_t*) &regs_out, sizeof(regs_out), false);
    return regs_out;
}

bool set(tm const& date_time) {
    uint8_t const frame[] = {
        0,
        binary_to_bcd(date_time.tm_sec),
        binary_to_bcd(date_time.tm_min),
        binary_to_bcd(date_time.tm_hour),
        binary_to_bcd(1),                       // This is of course wrong, but we don't care
        binary_to_bcd(date_time.tm_mday),
        uint8_t(((date_time.tm_year >= 2000) ? 0x80 : 0) | binary_to_bcd(date_time.tm_mon)),
        binary_to_bcd(date_time.tm_year % 100),
    };

    i2c_write_blocking(THE_I2C, THE_ADDRESS, &frame[0], sizeof(frame), false);
    return true;
}

tm to_tm(Registers const& regs) {
    return tm {
        .tm_sec =   bcd_to_binary(regs.seconds & 0x7f),
        .tm_min =   bcd_to_binary(regs.minutes & 0x7f),
        .tm_hour =  bcd_to_binary(regs.hours & 0x3f),
        .tm_mday =  bcd_to_binary(regs.day_of_month & 0x3f),
        .tm_mon =   bcd_to_binary(regs.month_century & 0x1f),
        .tm_year =  ((regs.month_century & 0x80) ? 2000 : 1900) + bcd_to_binary(regs.year),
    };
}

}
