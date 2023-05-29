#include "devprop.hpp"

#include "cobs.h"

#include <stdio.h>
#include <string.h>

static constexpr size_t MAX_FRAME_SIZE = 4 + 8 + 2;
// 1 delimiter, 4 id, 8 payload, 2 CRC, 1 stuffing, 1 delimiter
static constexpr size_t MAX_WIRE_FRAME_SIZE = 1 + MAX_FRAME_SIZE + 1 + 1;

dp_Node inst;

static uint16_t crc16_kermit(uint8_t *ptr, size_t count);
static void execute(uint8_t const* in_buf, size_t frame_length);

void app_dump_storage();

extern "C"
void dp_user_send_message_ext(dp_Node* inst,
                              uint32_t id,
                              uint8_t const* data,
                              size_t data_length) {
    // printf("MESSAGE %08X %zu\n", id, data_length);
    uint8_t frame_bytes[MAX_FRAME_SIZE];
    memcpy(frame_bytes + 0, &id, sizeof(id));
    memcpy(frame_bytes + 4, data, data_length);
    uint16_t crc = crc16_kermit(frame_bytes, 4 + data_length);
    memcpy(frame_bytes + 4 + data_length, &crc, sizeof(crc));

    uint8_t stuffed_bytes[MAX_WIRE_FRAME_SIZE];
    stuffed_bytes[0] = 0;            // reset decoder at receiving end
    size_t stuffed_length = 1 + cobsEncode(frame_bytes, 4 + data_length + 2, stuffed_bytes + 1);
    stuffed_bytes[stuffed_length++] = 0;

    fwrite(stuffed_bytes, stuffed_length, 1, stdout);
    fflush(stdout);
}

void DevpropReceiver::handle_recv(uint8_t b) {
    if (b == 0) {
        if (length > 0) {
            // un-stuff
            uint8_t unstuff_buffer[64];
            size_t unstuff_length = cobsDecode(in_buf, length, unstuff_buffer);

            if (unstuff_length >= 2) {
                // validate (check CRC)
                uint16_t crc = unstuff_buffer[unstuff_length - 2] | (unstuff_buffer[unstuff_length - 1] << 8);

                if (crc == crc16_kermit(unstuff_buffer, unstuff_length - 2)) {
                    // execute
                    execute(unstuff_buffer, unstuff_length - 2);
                }
            }
        }

        length = 0;
    }
    else if (length < sizeof(in_buf)) {
        if (length >= 4 && memcmp(in_buf + length - 4, "dump", 4) == 0 && (b == '\r' || b == '\n')) {
            printf("dumping storage\n");
            app_dump_storage();
            length = 0;
        }
        else {
            in_buf[length++] = b;
        }
    }
}

static uint16_t crc16_kermit(uint8_t *ptr, size_t count) {
    uint16_t crc = 0;

    for (; count > 0; ptr++, count--) {
        crc ^= *ptr;

        for (int i = 0; i < 8; i++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0x8408;
            }
            else {
                crc = crc >> 1;
            }
        }
    }

    return crc;
}

static void execute(uint8_t const* in_buf, size_t frame_length) {
    if (frame_length >= 4) {
        uint32_t id;
        memcpy(&id, in_buf, sizeof(id));

        dp_handle_message_ext(&inst, id, in_buf + 4, frame_length - 4);
    }
}
