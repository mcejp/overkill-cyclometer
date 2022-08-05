#pragma once

#include <stdint.h>

#include "devprop_bikECU.h"

extern dp_Node inst;

class DevpropReceiver {
public:
    void handle_recv(uint8_t b);

private:
    size_t length = 0;
    uint8_t in_buf[64];
};
