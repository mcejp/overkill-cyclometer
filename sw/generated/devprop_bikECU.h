#ifndef DEVPROP_bikECU_H
#define DEVPROP_bikECU_H

#include "devprop.h"

#ifdef __cplusplus
extern "C" {
#endif

enum { DP_NODE_ID_bikECU = 1 };

enum { INDEX_DISTANCE_TOTAL = 1 };
enum { INDEX_DISTANCE_TOTAL_RAW = 2 };
enum { INDEX_STORAGE_CAPACITY = 3 };
enum { INDEX_STORAGE_WRITEPOS = 4 };
enum { INDEX_CLOCK_YEAR = 5 };
enum { INDEX_CLOCK_MONTH = 6 };
enum { INDEX_CLOCK_DATE = 7 };
enum { INDEX_CLOCK_HOUR = 8 };
enum { INDEX_CLOCK_MINUTE = 9 };
enum { INDEX_CLOCK_SECOND = 10 };

void dp_node_init_bikECU(dp_Node* inst_out);

#ifdef __cplusplus
}
#endif

#endif