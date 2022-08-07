#pragma once

// https://datasheets.maximintegrated.com/en/ds/DS3231.pdf

#include <stdint.h>
#include <time.h>

namespace ds3231 {

struct Registers {
    uint8_t seconds;
    uint8_t minutes;
    uint8_t hours;
    uint8_t day_of_week;
    uint8_t day_of_month;
    uint8_t month_century;
    uint8_t year;
    uint8_t alarm1[5];
    uint8_t alarm2[4];
    uint8_t control;
    uint8_t control_status;
    uint8_t aging_offset;
    uint8_t msb_temp;
    uint8_t lsb_temp;
};

Registers read_registers();
bool set(tm const& date_time);
tm to_tm(Registers const& regs);

}
