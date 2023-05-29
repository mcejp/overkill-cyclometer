#include "app.hpp"
#include "draw.hpp"
#include "storage.hpp"

#include <optional>
#include <stdio.h>

using std::optional;

namespace app {
namespace {
    optional<TimeU64> last_saved;
    bool save_pending = false;

    constexpr int wheel_diameter_cm = 70;
    constexpr int wheel_circumference_cm = wheel_diameter_cm * 314 / 100;
}

void init() {
    printf("bikECU v%s\n", VERSION_STRING);
}

static void update_gui(float current_speed, float total_meters, SensorInputs const& inputs) {
    char buf[50];

    snprintf(buf, sizeof(buf), "%4.1f", current_speed);
    puttextat(font32x48, 0, 0, buf);

    puttextat(font8x12, (DISP_W - 4 * 8) / 8, 48, "km/h");

    snprintf(buf, sizeof(buf), "%8.2f", total_meters / 1000.0f);
    //puttextat(0, 2, buf);
    puttextat(font16x20, 0, 72, buf);
    puttextat(font8x12, (DISP_W - 2 * 8) / 8, 92, "km");

    if (save_pending) {
        puttextat(font16x20, 0, DISP_H - 20, "\x0f");
    }
    else {
        puttextat(font16x20, 0, DISP_H - 20, " ");
    }

    //storage_get_debug_str(buf, sizeof(buf));
    auto now = platform::get_current_time();
    snprintf(buf, sizeof(buf), "%02d:%02d:%02d  ", now.tm_hour, now.tm_min, now.tm_sec);
    puttextat(font8x12, 16 / 8 + 0, DISP_H - 16, buf);

    static int screen_counter = 0;

    // Show ambient temperature for 4 seconds
    if (screen_counter < 8) {
        snprintf(buf, sizeof(buf), "%2.0f\xf8" "C", platform::get_ambient_temperature());
        puttextat(font8x12, DISP_W / 8 - 4, DISP_H - 16, buf);
    }
    // Show battery voltage for 4 seconds
    else {
        snprintf(buf, sizeof(buf), "%3.1fV", platform::get_Vbat());
        puttextat(font8x12, DISP_W / 8 - 4, DISP_H - 16, buf);

        // Current measurement not good at the moment
        //snprintf(buf, sizeof(buf), "%4.2fA ", platform::get_Ibat());
        //puttextat(font8x12, DISP_W / 8 - 6, DISP_H - 16, buf);
    }

    screen_counter++;
    if (screen_counter >= 16) {
        screen_counter = 0;
    }

    // TODO: consider stateful widgets that recognize if/what they need to repaint as a result of newly assigned value
}

static uint64_t last_considered_event = 0;
static optional<int> saved_last_interval_us;

void wakecycle(TimeU64 now, EventBuffer const& events, SensorInputs const& inputs) {
    // count events since last considered
    // note that the event buffer is *not in order*
    uint64_t max_timestamp = 0;
    size_t max_timestamp_index;
    int num_events = 0;

    for (int i = 0; i < events.NUM_ENTRIES; i++) {
        if (events.timestamps[i] > last_considered_event) {
            num_events++;

            if (events.timestamps[i] > max_timestamp) {
                max_timestamp = events.timestamps[i];
                max_timestamp_index = i;
            }
        }
    }

    optional<int> last_interval_us;

    if (max_timestamp == 0) {
        // no new events

        if (last_considered_event != 0 && now / 1000 - last_considered_event / 1000 < MAX_INTERVAL_MS) {
            // ok...
            last_interval_us = saved_last_interval_us;
        }
    }
    else {
        // find previous-last event
        auto one_but_last_index = (events.NUM_ENTRIES + max_timestamp_index - 1) % events.NUM_ENTRIES;

        if (events.timestamps[one_but_last_index] > last_considered_event) {
            // yep
            last_interval_us = max_timestamp - events.timestamps[one_but_last_index];
        }
        else if (last_considered_event != 0) {
            // ok...
            last_interval_us = max_timestamp - last_considered_event;
        }
        else {
            // none!
        }

        last_considered_event = max_timestamp;
    }

    saved_last_interval_us = last_interval_us;

    // estimate speed
    //const auto velocity_cm_per_second = num_events * wheel_circumference_cm;
    //const auto velocity_m_per_hour = velocity_cm_per_second * 3600 / 100;

    // printf("[%6d] %3d events / ", (int) (now / 1000), num_events);

    if (num_events > 0) {
        bikECU_globals.rev_count += num_events;
        save_pending = true;
    }

    float total_meters = bikECU_globals.rev_count * (wheel_circumference_cm / 100.0f);

    if (last_interval_us.has_value()) {
        // v = o / dt
        // wheel_circumference_cm * 3.6M ~~ 792M
        // FIXME: SIGFPE risk
        const auto velocity_cm_per_hour = wheel_circumference_cm * 3'600'000 / (*last_interval_us / 1000);
        const auto velocity_m_per_hour = velocity_cm_per_hour / 100;

        //printf("%7d us interval / %5d m/h\n", *last_interval_us, velocity_m_per_hour);
        app::update_gui(velocity_m_per_hour / 1000.0f, total_meters, inputs);
    }
    else {
        //printf("------- us interval / ----- m/h\n");
        app::update_gui(0.0f, total_meters, inputs);
    }

    /* Desired logic:
        - if data changed, and
            elapsed > 30 sec from last write
            or elapsed > 10 sec from last write && speed == 0 for 3 seconds
     */
    if (save_pending) {
        if (!last_saved.has_value()) {
            last_saved = now;
        }
        else if (now - *last_saved >= 30'000'000 || (now - *last_saved >= 10'000'000 && now - last_considered_event >= 3'000'000)) {
            printf("Saving total distance to flash.\n");
            last_saved = now;
            save_pending = false;

            static int seq = 0;
            auto now = platform::get_current_time();

            storage_save_value(bikECU_globals.rev_count, seq, now);
            seq++;
        }
    }
}

extern "C" uint32_t get_Distance_Total(int* error_out) {
    float total_meters = bikECU_globals.rev_count * (wheel_circumference_cm / 100.0f);
    return (uint32_t) total_meters;
}

extern "C" uint16_t get_Distance_Total_Raw(int* error_out) {
    return bikECU_globals.rev_count;
}

extern "C" uint32_t set_Distance_Total_Raw(uint32_t value, int* error_out) {
    // *error_out = DP_NOT_IMPLEMENTED;         TODO fix in GUI
    bikECU_globals.rev_count = value;
    return value;
}

}
