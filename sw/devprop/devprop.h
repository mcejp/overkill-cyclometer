#ifndef DEVPROP_H
#define DEVPROP_H

#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*dp_GenericCallback)();

typedef enum dp_DataType {
    DP_UINT8,
    DP_UINT16,
    DP_UINT32,
} dp_DataType;

typedef enum dp_ErrorCode {
    DP_OK = 0,
    DP_GENERIC_ERROR = -1,
    DP_PROTOCOL_ERROR = -2,
    DP_NOT_IMPLEMENTED = -3,
    DP_INTERNAL_ERROR = -4,
    DP_VALUE_ERROR = -5,
} dp_ErrorCode;

typedef struct dp_Property {
    dp_DataType type;
    dp_GenericCallback user_get_value;
    dp_GenericCallback user_set_value;

    // TODO: limits for WRITE operations
} dp_Property;

// This structure should be treated as opaque by the user
typedef struct {
    uint8_t const* manifest_bytes;
    dp_Property const* property_table;
    uint16_t manifest_length;
    uint8_t node_id;
    uint8_t num_properties;

    // TODO: an untyped 'user' pointer field could also be provided, with getter & setter functions
} dp_Node;

void dp_node_init(dp_Node* inst_out,
                  int node_id,
                  uint8_t const* manifest_bytes,
                  size_t manifest_length,
                  dp_Property const* property_table,
                  size_t num_properties
                  );
void dp_handle_message_ext(dp_Node* inst, uint32_t id, uint8_t const* data, size_t data_length);

void dp_user_send_message_ext(dp_Node* inst, uint32_t id, uint8_t const* data, size_t data_length);

#ifdef __cplusplus
}
#endif

#endif
