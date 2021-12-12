#include "app.hpp"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>

#include "libretro.h"

static uint32_t *frame_buf;
static struct retro_log_callback logging;
static retro_log_printf_t log_cb;

static void fallback_log(enum retro_log_level level, const char *fmt, ...)
{
   (void)level;
   va_list va;
   va_start(va, fmt);
   vfprintf(stderr, fmt, va);
   va_end(va);
}

void retro_init(void)
{
   frame_buf = (uint32_t*) calloc(128 * 128, sizeof(uint32_t));
}

void retro_deinit(void)
{
   free(frame_buf);
   frame_buf = NULL;
}

unsigned retro_api_version(void)
{
   return RETRO_API_VERSION;
}

void retro_set_controller_port_device(unsigned port, unsigned device)
{
   log_cb(RETRO_LOG_INFO, "Plugging device %u into port %u.\n", device, port);
}

void retro_get_system_info(struct retro_system_info *info)
{
   memset(info, 0, sizeof(*info));
   info->library_name     = "TestCore";
   info->library_version  = "v1";
   info->need_fullpath    = false;
   info->valid_extensions = NULL; // Anything is fine, we don't care.
}

static retro_video_refresh_t video_cb;
static retro_audio_sample_t audio_cb;
static retro_audio_sample_batch_t audio_batch_cb;
static retro_environment_t environ_cb;
static retro_input_poll_t input_poll_cb;
static retro_input_state_t input_state_cb;

void retro_get_system_av_info(struct retro_system_av_info *info)
{
   info->timing = (struct retro_system_timing) {
      .fps = 60.0,
      .sample_rate = 0.0,
   };

   info->geometry = (struct retro_game_geometry) {
      .base_width   = 128,
      .base_height  = 128,
      .max_width    = 128,
      .max_height   = 128,
      .aspect_ratio = 1.0f,
   };
}

void retro_set_environment(retro_environment_t cb)
{
   environ_cb = cb;

   bool no_content = true;
   cb(RETRO_ENVIRONMENT_SET_SUPPORT_NO_GAME, &no_content);

   if (cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &logging))
      log_cb = logging.log;
   else
      log_cb = fallback_log;
}

void retro_set_audio_sample(retro_audio_sample_t cb)
{
   audio_cb = cb;
}

void retro_set_audio_sample_batch(retro_audio_sample_batch_t cb)
{
   audio_batch_cb = cb;
}

void retro_set_input_poll(retro_input_poll_t cb)
{
   input_poll_cb = cb;
}

void retro_set_input_state(retro_input_state_t cb)
{
   input_state_cb = cb;
}

void retro_set_video_refresh(retro_video_refresh_t cb)
{
   video_cb = cb;
}

static unsigned x_coord;
static unsigned y_coord;
static int mouse_rel_x;
static int mouse_rel_y;

void retro_reset(void)
{
   x_coord = 0;
   y_coord = 0;
}

static void update_input(void)
{
   input_poll_cb();
   if (input_state_cb(0, RETRO_DEVICE_JOYPAD, 0, RETRO_DEVICE_ID_JOYPAD_UP))
   {
      /* stub */
   }
}

static void check_variables(void)
{
}

static void audio_callback(void)
{
   audio_cb(0, 0);
}

static EventBuffer evb {};
int when = 0;

static void simulate_events(int count, int dt_usec) {
    while (count--) {
        static int idx = 0;

        when += dt_usec;
        evb.timestamps[idx] = when;
        idx = (idx + 1) % evb.NUM_ENTRIES;
    }
}

void retro_run(void)
{
   update_input();

   static int frame_cnt = 0;
   static int the_time = 0;
   static float velocity = 0.0f;
   static float acceleration = 0.0f;

   if (frame_cnt++ == UPDATE_PERIOD_MS / 17) {      // assuming 16.7ms/frame
       acceleration += (rand() % 50 - 25) * 0.01f * (UPDATE_PERIOD_MS / 1000.0f);
       velocity += acceleration;
       //velocity = 4 / 3.6f;
       if (velocity < 0) {
           velocity = 0.0f;
           acceleration = std::max(acceleration, 0.0f);    // anti-windup
       }
       else if (velocity >= 60 / 3.6f) {
           velocity = 60 / 3.6f;
           acceleration = std::min(acceleration, 0.0f);    // anti-windup
       }

       static float events_owed = 0.0f;
       events_owed += 0.5f * velocity / (0.7f * 3.14f);

       while (events_owed >= 1.0f) {
           // TODO: this is still not good enough -- must ensure that timestamps corresponds to 'the_time'
           simulate_events(1, 1e6f / (velocity / (0.7f * 3.14f)));
           events_owed -= 1.0f;
       }
       the_time += UPDATE_PERIOD_MS * 1000;
       app::wakecycle(the_time, evb, app::SensorInputs { 20.0f });
       frame_cnt = 0;
   }

   //render_checkered();
   video_cb(frame_buf, 128, 128, 128 * 4);
   audio_callback();

   bool updated = false;
   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated)
      check_variables();
}

bool retro_load_game(const struct retro_game_info *info)
{
   app::init();

   enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_XRGB8888;
   if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt))
   {
      log_cb(RETRO_LOG_INFO, "XRGB8888 is not supported.\n");
      return false;
   }

   check_variables();

   (void)info;
   return true;
}

void retro_unload_game(void)
{
}

unsigned retro_get_region(void)
{
   return RETRO_REGION_NTSC;
}

bool retro_load_game_special(unsigned type, const struct retro_game_info *info, size_t num)
{
   if (type != 0x200)
      return false;
   if (num != 2)
      return false;
   return retro_load_game(NULL);
}

size_t retro_serialize_size(void)
{
   return 2;
}

bool retro_serialize(void *data_, size_t size)
{
   if (size < 2)
      return false;

   uint8_t *data = (uint8_t*) data_;
   data[0] = x_coord;
   data[1] = y_coord;
   return true;
}

bool retro_unserialize(const void *data_, size_t size)
{
   if (size < 2)
      return false;

   const uint8_t *data = (uint8_t*) data_;
   x_coord = data[0] & 31;
   y_coord = data[1] & 31;
   return true;
}

void *retro_get_memory_data(unsigned id)
{
   (void)id;
   return NULL;
}

size_t retro_get_memory_size(unsigned id)
{
   (void)id;
   return 0;
}

void retro_cheat_reset(void)
{}

void retro_cheat_set(unsigned index, bool enabled, const char *code)
{
   (void)index;
   (void)enabled;
   (void)code;
}

/////////////////

static int draw_row, draw_column;

void platformSendData(unsigned char data) {
    int true_row = 127 - draw_column;
    int true_col = draw_row * 8;
    for (int i = 0; i < 8; i++)
        frame_buf[(true_row) * 128 + true_col + i] = (data & (1<<i)) ? 0xffffffff : 0xff000000;
    draw_column = (draw_column + 1) % 128;
}

void setTextXY(unsigned char Row, unsigned char Column) {
    draw_row = Row;
    draw_column = Column;
}

