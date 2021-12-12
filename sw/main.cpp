#include "app.hpp"
#include "storage.hpp"
#include "SeeedGrayOLED.h"

#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "hardware/sync.h"
#include "pico/stdlib.h"

#include <stdio.h>
#include <string.h>

using std::optional;

static void adc_demo() {
    adc_init();

    // Make sure GPIO is high-impedance, no pullups etc
    //adc_gpio_init(26);
    // Select ADC input 0 (GPIO26)
    //adc_select_input(0);

    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    //sleep_ms(1000);
    //
    //for (int i = 0; i < 5; i++) {
    //    // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
    //    const float conversion_factor = 3.3f / (1 << 12);
    //    uint16_t result = adc_read();
    //    auto ADC_Voltage = result * conversion_factor;
    //    auto T = 27 - (ADC_Voltage - 0.706f)/0.001721f;
    //    printf("Raw value: 0x%03x, voltage: %f V, temp: %.1f degC\n", result, result * conversion_factor, T);
    //    sleep_ms(500);
    //}
    //
    //adc_set_temp_sensor_enabled(false);
}

void platformSendCommand(unsigned char command) {
    i2c_inst_t *i2c = i2c0;
    uint8_t data[2];
    data[0] = SeeedGrayOLED_Command_Mode;
    data[1] = command;

    i2c_write_blocking(i2c, SeeedGrayOLED_Address, data, 2, false);
}

void platformSendData(unsigned char command) {
    i2c_inst_t *i2c = i2c0;
    uint8_t data[2];
    data[0] = SeeedGrayOLED_Data_Mode;
    data[1] = command;

    i2c_write_blocking(i2c, SeeedGrayOLED_Address, data, 2, false);
}

static void i2c_demo() {
    i2c_inst_t *i2c = i2c0;

    printf("I2C demo\n");

    i2c_init(i2c, 400 * 1000);

    // Pins
    const uint sda_pin = 8;
    const uint scl_pin = 9;

    gpio_set_function(sda_pin, GPIO_FUNC_I2C);
    gpio_set_function(scl_pin, GPIO_FUNC_I2C);
    gpio_pull_up(sda_pin);
    gpio_pull_up(scl_pin);

    SeeedGrayOled.init(SH1107G);             //initialize SEEED OLED display
    SeeedGrayOled.clearDisplay();     //Clear Display.
    SeeedGrayOled.setNormalDisplay(); //Set Normal Display Mode
    SeeedGrayOled.setVerticalMode();  // Set to vertical mode for displaying text

    //for (char i = 0; i < 16 ; i++) {
    //    SeeedGrayOled.setTextXY(i, 0); //set Cursor to ith line, 0th column
    //    SeeedGrayOled.setGrayLevel(i); //Set Grayscale level. Any number between 0 - 15.
    //    SeeedGrayOled.putString("Hello World OLED"); //Print Hello World
    //}

    printf("I2C demo done\n");
}

const uint LED_PIN = PICO_DEFAULT_LED_PIN;
const uint MY_INPUT_PIN = 22;

static volatile EventBuffer evb;

// https://github.com/raspberrypi/pico-examples/blob/master/gpio/hello_gpio_irq/hello_gpio_irq.c
static void gpio_callback(uint gpio, uint32_t events) {
    gpio_put(LED_PIN, !gpio_get(MY_INPUT_PIN));

    if (events & GPIO_IRQ_EDGE_FALL) {
        auto now = time_us_64();

        static uint64_t last_timestamp = 0;
        static uint32_t idx = 0;

        if (now > last_timestamp + MIN_INTERVAL_MS * 1000) {
            evb.timestamps[idx] = now;
            idx = (idx + 1) % evb.NUM_ENTRIES;
            last_timestamp = now;
        }
    }
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
int main() {
    stdio_init_all();
    //sleep_ms(1000);

    adc_demo();

    gpio_init(MY_INPUT_PIN);
    gpio_set_dir(MY_INPUT_PIN, GPIO_IN);
    gpio_pull_up(MY_INPUT_PIN);

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    gpio_put(LED_PIN, 1);
    sleep_ms(100);
    gpio_put(LED_PIN, 0);

    i2c_demo();

    storage_init();

    auto next_wakeup = get_absolute_time();

    //printf("entering app.\n");
    app::init();

    gpio_set_irq_enabled_with_callback(MY_INPUT_PIN, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &gpio_callback);

    while (true) {
        // TODO: interrupt-driven wake up can save a tiny bit of power
        sleep_ms(50);

        auto now = get_absolute_time();

        // wake-up due?
        if (absolute_time_diff_us(next_wakeup, now) >= 0) {
            next_wakeup = delayed_by_ms(next_wakeup, UPDATE_PERIOD_MS);

            // read temperature sensor
            // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
            const float conversion_factor = 3.3f / (1 << 12);
            uint16_t result = adc_read();
            auto ADC_Voltage = result * conversion_factor;
            auto temp = 27 - (ADC_Voltage - 0.706f)/0.001721f;
            //printf("Raw value: 0x%03x, voltage: %f V, temp: %.1f degC\n", result, result * conversion_factor, T);

            EventBuffer evb_snapshot;

            // TODO: is this C++-legal?
            uint32_t ints = save_and_disable_interrupts();
            memcpy(&evb_snapshot, (const void*) &evb, sizeof(evb));
            restore_interrupts(ints);

            app::wakecycle(to_us_since_boot(now), evb_snapshot, app::SensorInputs { temp });
        }
    }
}

#pragma clang diagnostic pop
