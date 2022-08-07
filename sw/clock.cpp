#include "devprop.hpp"
#include "ds3231.hpp"

template <typename T>
int update_field(T tm::*field, int value, int* error_out) {
    auto tm = ds3231::to_tm(ds3231::read_registers());
    tm.*field = value;
    *error_out = ds3231::set(tm) ? DP_OK : DP_VALUE_ERROR;
    return value;
}

extern "C" {

uint8_t get_Clock_Date(int* error_out) {
    return ds3231::to_tm(ds3231::read_registers()).tm_mday;
}

uint8_t get_Clock_Hour(int* error_out) {
    return ds3231::to_tm(ds3231::read_registers()).tm_hour;
}

uint8_t get_Clock_Minute(int* error_out) {
    return ds3231::to_tm(ds3231::read_registers()).tm_min;
}

uint8_t get_Clock_Month(int* error_out) {
    return ds3231::to_tm(ds3231::read_registers()).tm_mon;
}

uint8_t get_Clock_Second(int* error_out) {
    return ds3231::to_tm(ds3231::read_registers()).tm_sec;
}

uint16_t get_Clock_Year(int* error_out) {
    return ds3231::to_tm(ds3231::read_registers()).tm_year;
}

uint8_t set_Clock_Date(uint8_t value, int* error_out) {
    return update_field(&tm::tm_mday, value, error_out);
}

uint8_t set_Clock_Hour(uint8_t value, int* error_out) {
    return update_field(&tm::tm_hour, value, error_out);
}

uint8_t set_Clock_Minute(uint8_t value, int* error_out) {
    return update_field(&tm::tm_min, value, error_out);
}

uint8_t set_Clock_Month(uint8_t value, int* error_out) {
    return update_field(&tm::tm_mon, value, error_out);
}

uint8_t set_Clock_Second(uint8_t value, int* error_out) {
    return update_field(&tm::tm_sec, value, error_out);
}

uint16_t set_Clock_Year(uint16_t value, int* error_out) {
    return update_field(&tm::tm_year, value, error_out);
}

}
