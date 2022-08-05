#include "devprop_can_ext_v1.h"

#include <assert.h>

typedef uint8_t (*get_value_uint8_t)(int* error_out);
typedef uint16_t (*get_value_uint16_t)(int* error_out);
typedef uint32_t (*get_value_uint32_t)(int* error_out);

typedef uint8_t (*set_value_uint8_t)(uint8_t value, int* error_out);
typedef uint16_t (*set_value_uint16_t)(uint16_t value, int* error_out);
typedef uint32_t (*set_value_uint32_t)(uint32_t value, int* error_out);

enum { CAN_MSG_MAX_SIZE = 8 };
enum { MAX_ERROR_CODE = 255 };
enum { MAX_NODE_ID = 31 };
enum { MIN_PROPERTY_INDEX = 1 };
enum { MAX_PROPERTY_INDEX = 255 };
enum { SEGMENT_SIZE = 8 };

enum { DIR_MASK = 1 << 16 };

typedef struct {
    uint8_t bytes[CAN_MSG_MAX_SIZE];
} CanMsgBuffer;

static int get_property_value(dp_Property const* prop, CanMsgBuffer* buffer_out);
static int set_property_value(dp_Property const* prop, uint8_t const* bytes, size_t length, CanMsgBuffer* buffer_out);
static void send_error(dp_Node* inst, uint32_t id, dp_ErrorCode error_code);

void dp_node_init(dp_Node* inst,
                  int node_id,
                  uint8_t const* manifest_bytes,
                  size_t manifest_length,
                  dp_Property const* property_table,
                  size_t num_properties
                  ) {
    assert(node_id >= 0);
    assert(node_id <= MAX_NODE_ID);

    inst->node_id = node_id;
    inst->manifest_bytes = manifest_bytes;
    inst->manifest_length = manifest_length;
    inst->property_table = property_table;
    inst->num_properties = num_properties;
}

void dp_handle_message_ext(dp_Node* inst, uint32_t id, uint8_t const* data, size_t data_length) {
	if ((id & DPP_ID_FIXED_MASK) != DPP_ID_FIXED_PART) {
	    return;
	}

    int property_index = (id & 0xFF);
    int opcode = (id >> 8) & 7;
    int node_id = (id >> 11) & 31;
    int dir = (id >> 16) & 1;

    if (node_id != inst->node_id || dir != DPP_CLIENT_TO_DEVICE) {
        return;
    }

    CanMsgBuffer resp_buffer;

    switch (opcode) {
        case DPP_READ_MANIFEST: {
            if (data_length != 0) {
                send_error(inst, id, DP_PROTOCOL_ERROR);
                break;
            }

            int offset = property_index * SEGMENT_SIZE;
            int valid_length = inst->manifest_length - offset;
            if (valid_length < 0) {
                valid_length = 0;
            }
            else if (valid_length > SEGMENT_SIZE) {
                valid_length = SEGMENT_SIZE;
            }

            dp_user_send_message_ext(inst, id ^ DIR_MASK, inst->manifest_bytes + offset, valid_length);
            break;
        }

        case DPP_READ_PROPERTY: {
            int real_property_index = property_index - 1;
            if (real_property_index < 0 ||
                    real_property_index > inst->num_properties ||
                    data_length != 0) {
                send_error(inst, id, DP_PROTOCOL_ERROR);
                break;
            }

            int rc = get_property_value(&inst->property_table[real_property_index], &resp_buffer);
            if (rc >= 0) {
                assert(rc > 0);
                assert(rc < CAN_MSG_MAX_SIZE);

                // should never be 0, but to save code here we just let the client deal with it
                dp_user_send_message_ext(inst, id ^ DIR_MASK, resp_buffer.bytes, rc);
            }
            else {
                send_error(inst, id, rc);
            }
            break;
        }

        case DPP_WRITE_PROPERTY: {
            int real_property_index = property_index - 1;
            if (real_property_index < 0 || real_property_index > inst->num_properties) {
                send_error(inst, id, DP_PROTOCOL_ERROR);
                break;
            }

            int rc = set_property_value(&inst->property_table[real_property_index], data, data_length, &resp_buffer);
            if (rc >= 0) {
                assert(rc > 0);
                assert(rc < CAN_MSG_MAX_SIZE);

                // should never be 0, but to save code here we just let the client deal with it
                dp_user_send_message_ext(inst, id ^ DIR_MASK, resp_buffer.bytes, rc);
            }
            else {
                send_error(inst, id, rc);
            }
            break;
        }
    }
}

static int get_property_value(dp_Property const* prop, CanMsgBuffer* buffer_out) {
    int rc = 0;

    if (!prop->user_get_value) {
        return DP_VALUE_ERROR;
    }

    switch (prop->type) {
        case DP_UINT8: {
            uint8_t value = ((get_value_uint8_t)(prop->user_get_value))(&rc);

            if (rc >= 0) {
                assert(rc == 0);
                buffer_out->bytes[0] = (value & 0xff);
                return 1;
            }
            break;
        }

        case DP_UINT16: {
            uint16_t value = ((get_value_uint16_t)(prop->user_get_value))(&rc);

            if (rc >= 0) {
                assert(rc == 0);
                buffer_out->bytes[0] = (value & 0xff);
                buffer_out->bytes[1] = ((value >> 8) & 0xff);
                return 2;
            }
            break;
        }

        case DP_UINT32: {
            uint32_t value = ((get_value_uint32_t)(prop->user_get_value))(&rc);

            if (rc >= 0) {
                assert(rc == 0);
                buffer_out->bytes[0] = (value & 0xff);
                buffer_out->bytes[1] = ((value >> 8) & 0xff);
                buffer_out->bytes[2] = ((value >> 16) & 0xff);
                buffer_out->bytes[3] = ((value >> 24) & 0xff);
                return 4;
            }
            break;
        }

        default:
            // property has an unsupported (or invalid) type
            rc = DP_NOT_IMPLEMENTED;
    }

    return rc;
}

uint32_t dpp_make_id(int dir, int node_id, dpp_Opcode opcode, int property_index) {
    if (opcode == DPP_READ_PROPERTY || opcode == DPP_WRITE_PROPERTY) {
	    assert(property_index >= MIN_PROPERTY_INDEX);
	    assert(property_index <= MAX_PROPERTY_INDEX);
	}
	else {
	    assert(property_index >= 0);
    	assert(property_index <= UINT8_MAX);
	}

    assert(opcode >= 0);
    assert(opcode <= DPP_MAX_OPCODE);
    assert(node_id >= 0);
    assert(node_id < MAX_NODE_ID);
    assert(dir == 0 || dir == 1);

    return DPP_ID_FIXED_PART | (dir << 16) | (node_id << 11) | (opcode << 8) | property_index;
}

static void send_error(dp_Node* inst, uint32_t id, dp_ErrorCode error_code) {
    assert(error_code < 0);
    assert(error_code >= -MAX_ERROR_CODE);

    int property_index = (id & 0xFF);
    int opcode = (id >> 8) & 7;
    int node_id = (id >> 11) & 31;
    int dir = (id >> 16) & 1;

    assert(node_id == inst->node_id);
    assert(dir == DPP_CLIENT_TO_DEVICE);

    uint8_t payload[2];
    payload[0] = opcode;
    payload[1] = -error_code;   // internally we use negative error codes, but for transmission they need to be positive

    dp_user_send_message_ext(inst, dpp_make_id(DPP_DEVICE_TO_CLIENT, node_id, DPP_ERROR, property_index), payload, sizeof(payload));
}

static int set_property_value(dp_Property const* prop, uint8_t const* value_bytes, size_t value_length, CanMsgBuffer* buffer_out) {
    int rc = 0;

    if (!prop->user_set_value) {
        return DP_VALUE_ERROR;
    }

    switch (prop->type) {
        case DP_UINT8: {
            if (value_length != 1) {
                return DP_PROTOCOL_ERROR;
            }

            uint8_t value = value_bytes[0];
            value = ((set_value_uint8_t)(prop->user_set_value))(value, &rc);

            if (rc >= 0) {
                assert(rc == 0);
                buffer_out->bytes[0] = (value & 0xff);
                return 1;
            }
            break;
        }

        case DP_UINT16: {
            if (value_length != 2) {
                return DP_PROTOCOL_ERROR;
            }

            uint16_t value = value_bytes[0] | (value_bytes[1] << 8);
            value = ((set_value_uint16_t)(prop->user_set_value))(value, &rc);

            if (rc >= 0) {
                assert(rc == 0);
                buffer_out->bytes[0] = (value & 0xff);
                buffer_out->bytes[1] = ((value >> 8) & 0xff);
                return 2;
            }
            break;
        }

        case DP_UINT32: {
            if (value_length != 4) {
                return DP_PROTOCOL_ERROR;
            }

            uint32_t value = value_bytes[0] | (value_bytes[1] << 8) | (value_bytes[2] << 16) | (value_bytes[3] << 24);
            value = ((set_value_uint32_t)(prop->user_set_value))(value, &rc);

            if (rc >= 0) {
                assert(rc == 0);
                buffer_out->bytes[0] = (value & 0xff);
                buffer_out->bytes[1] = ((value >> 8) & 0xff);
                buffer_out->bytes[2] = ((value >> 16) & 0xff);
                buffer_out->bytes[3] = ((value >> 24) & 0xff);
                return 4;
            }
            break;
        }

        default:
            // property has an unsupported (or invalid) type
            rc = DP_NOT_IMPLEMENTED;
    }

    return rc;
}
