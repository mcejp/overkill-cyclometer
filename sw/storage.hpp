#ifndef BIKECU_STORAGE_HPP
#define BIKECU_STORAGE_HPP

#include <stdint.h>
#include <stdlib.h>

struct Global_data {
    uint32_t rev_count;
};

extern Global_data bikECU_globals;

extern bool flash_was_formatted;

void storage_init();
void storage_save_value(uint32_t value);

void storage_get_debug_str(char* buf, size_t bufsiz);

#endif //BIKECU_STORAGE_HPP
