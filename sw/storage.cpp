#include "storage.hpp"

#ifdef PICO_BUILD
#include "hardware/flash.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"
#endif

#include <stdio.h>
#include <string.h>

#ifndef PICO_BUILD
enum { FLASH_SECTOR_SIZE = 4096 };
enum { FLASH_PAGE_SIZE = 256 };
#endif

static inline uint8_t flash_magic[] = "\xAA" "bikECU\xBB";
static inline size_t flash_offset = 256 * 1024;
static inline size_t flash_num_sectors = 32;            // onboard flash is 16M, so there's no shortage
const int FLASH_ERASE_PAGE_SIZE = FLASH_SECTOR_SIZE;
const int FLASH_WRITE_PAGE_SIZE = FLASH_PAGE_SIZE;

#ifdef PICO_BUILD
static inline uint8_t const* FLASH_READ_ADDR = ((uint8_t*) XIP_BASE) + flash_offset;
#endif

struct Flash_header {
    uint8_t magic[8];
    uint16_t version;
    uint16_t generation;
    uint16_t reserved_;
    uint16_t header_checksum;
    uint8_t pad[FLASH_WRITE_PAGE_SIZE - 16];
};

Global_data bikECU_globals;

struct Flash_record {
    uint32_t value;
    uint32_t value_checksum;
    uint8_t pad[FLASH_WRITE_PAGE_SIZE - 8];
};

static inline size_t Flash_record_real_size = 8;

static_assert(sizeof(Flash_header) == FLASH_WRITE_PAGE_SIZE);
static_assert(sizeof(Flash_record) == FLASH_WRITE_PAGE_SIZE);

static inline int MAX_FLASH_RECORDS = (flash_num_sectors * FLASH_ERASE_PAGE_SIZE - sizeof(Flash_header)) / sizeof(Flash_record);

bool flash_was_formatted = false;
int flash_write_pos = 0;

#ifdef PICO_BUILD
static void format_flash() {
    Flash_header hdr;

    memset(&hdr, 0, sizeof(hdr));
    memcpy(hdr.magic, flash_magic, 8);
    hdr.version = 1;
    hdr.generation = 0;
    hdr.header_checksum = 65535 - hdr.generation;

    uint32_t ints = save_and_disable_interrupts();
    flash_range_erase(flash_offset, FLASH_ERASE_PAGE_SIZE * flash_num_sectors);
    flash_range_program(flash_offset, (uint8_t const*) &hdr, sizeof(hdr));
    restore_interrupts(ints);

    // TODO: to fully format, must also erase any other candidate data pages

    flash_was_formatted = true;
}

void storage_init() {
    Flash_header hdr;
    memcpy(&hdr, FLASH_READ_ADDR, sizeof(hdr));

    bikECU_globals.rev_count = 0;

    if (memcmp(hdr.magic, flash_magic, 8) != 0 || hdr.version != 1 || hdr.header_checksum != 65535 - hdr.generation) {
        printf("storage_init: Invalid header (%02X, %d, %d); formatting.\n", hdr.magic[0], hdr.version, hdr.header_checksum);
        format_flash();
        flash_write_pos = 0;
    }
    else {
        for (flash_write_pos = 0; flash_write_pos < MAX_FLASH_RECORDS; flash_write_pos++) {
            Flash_record rec;
            memcpy(&rec, FLASH_READ_ADDR + sizeof(hdr) + flash_write_pos * sizeof(Flash_record), Flash_record_real_size);

            bool is_valid = (rec.value_checksum == 0x80000000 - rec.value);

            if (is_valid) {
                bikECU_globals.rev_count = rec.value;
            }
            else {
                // TODO: check if FFFF, otherwise signal corruption & re-format
                break;
            }
        }

        printf("storage_init: Ok, resuming @ %d with data value %d.\n", flash_write_pos, bikECU_globals.rev_count);
    }
}

void storage_save_value(uint32_t value) {
    // TODO: check if FFFF, otherwise signal corruption & format flash

    if (flash_write_pos == MAX_FLASH_RECORDS) {
        printf("storage_init: Storage exhausted, reformatting.\n");
        format_flash();
        flash_write_pos = 0;
    }

    Flash_record rec;
    rec.value = value;
    rec.value_checksum = 0x80000000 - rec.value;

    uint32_t ints = save_and_disable_interrupts();
    flash_range_program(flash_offset + sizeof(Flash_header) + flash_write_pos * FLASH_WRITE_PAGE_SIZE, (uint8_t const*) &rec, sizeof(rec));
    restore_interrupts(ints);

    flash_write_pos++;
}
#else
void storage_save_value(uint32_t value) {
    if (flash_write_pos == MAX_FLASH_RECORDS) {
        printf("storage_init: Storage exhausted, reformatting.\n");
        flash_write_pos = 0;
    }

    flash_write_pos++;
}
#endif

void storage_get_debug_str(char* buf, size_t bufsiz) {
    snprintf(buf, bufsiz, "%c%3d", flash_was_formatted ? 'F' : ' ', flash_write_pos);
}

extern "C" uint16_t get_Storage_Capacity(int* error_out) {
    return MAX_FLASH_RECORDS;
}

extern "C" uint16_t get_Storage_WritePos(int* error_out) {
    return flash_write_pos;
}
