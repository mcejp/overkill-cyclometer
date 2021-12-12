#include <optional>
#include <stdint.h>

inline char VERSION_STRING[] = "1.1.0";

inline int MIN_EVENT_LEN_US = 1000;  // ~1.67 cm travel at 60 km/h
inline int MIN_INTERVAL_MS = 132;    // (70 cm * pi) / (60 km/h)
// max event rate ~ 7.6 ev/sec
inline int MAX_INTERVAL_MS = 2000;   // ~(70 cm * pi) / (4 km/h)
inline int UPDATE_PERIOD_MS = 500;

inline int DISP_W = 128;
inline int DISP_H = 128;

struct EventBuffer {
    enum { NUM_ENTRIES = 16 };

    uint64_t timestamps[NUM_ENTRIES];
};

using TimeU64 = uint64_t;

namespace app {
    struct SensorInputs {
        float temp_degC;
    };

    void init();
    //void update_gui(float current_speed, float total_meters);
    void wakecycle(TimeU64 now, EventBuffer const& events, SensorInputs const& inputs);
}
