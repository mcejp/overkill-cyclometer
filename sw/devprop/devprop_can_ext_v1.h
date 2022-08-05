#ifndef DEVPROP_CAN_EXT_V1_H
#define DEVPROP_CAN_EXT_V1_H

#include "devprop.h"

// private types & functions -- should be generally only used for test purposes, as they relate to a specific protocol implementation
// ID_FIXED_MASK can be useful for configuring message filters, though

enum { DPP_ID_FIXED_MASK = 0x1FFE0000 };
enum { DPP_ID_FIXED_PART = 0x1EF00000 };

typedef enum dpp_Opcode {
    DPP_READ_MANIFEST = 0,
    DPP_READ_PROPERTY = 1,
    DPP_WRITE_PROPERTY = 2,
    DPP_ERROR = 7,
    DPP_MAX_OPCODE = 7,
} dpp_Opcode;

enum {
    DPP_DEVICE_TO_CLIENT = 0,
    DPP_CLIENT_TO_DEVICE = 1,
};

uint32_t dpp_make_id(int dir, int node_id, dpp_Opcode opcode, int property_index);

#endif
