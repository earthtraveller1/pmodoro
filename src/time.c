#include <stdlib.h>

#include <raylib.h>

#include "constants.h"
#include "time.h"

void time_inc_mins(struct time* time, unsigned int mins) {
    int new_mins = time->minutes + mins;
    if (new_mins < 100) {
        time->minutes = new_mins;
    }
}

void time_dec_mins(struct time* time, unsigned int mins) {
    int new_mins = time->minutes - mins;
    if (new_mins >= 0) {
        time->minutes = new_mins;
    }
}

void time_inc_secs(struct time* time, unsigned int secs) {
    int new_secs = time->seconds + secs;
    if (new_secs >= 60) {
        time->seconds = new_secs % 60;
        time_inc_mins(time, new_secs / 60);

        return;
    }

    time->seconds = new_secs;
}

void time_dec_secs(struct time* time, unsigned int secs) {
    int new_secs = time->seconds - secs;
    if (new_secs < 0) {
        time->seconds = abs(new_secs % 60);
        time_dec_mins(time, abs(new_secs / 60));

        return;
    }

    time->seconds = new_secs;
}

void draw_time(const struct time* time, float ypos) {
    const float digit_gap = 60.0;
    const float total_width = digit_gap * 5;
    const float minute_margin = (WIDTH - total_width) / 2.0;

    char minute_tens[] = { time->minutes / 10 + 48, 0 };
    char minute_ones[] = { time->minutes % 10 + 48, 0 };

    char second_tens[] = { time->seconds / 10 + 48, 0 };
    char second_ones[] = { time->seconds % 10 + 48, 0 };

    DrawText(minute_tens, minute_margin, ypos, TIME_FONT_SIZE, FONT_COLOR);
    DrawText(minute_ones, minute_margin + digit_gap, ypos, TIME_FONT_SIZE, FONT_COLOR);
    DrawText(":", minute_margin + digit_gap * 2 + 20.0, ypos, TIME_FONT_SIZE, FONT_COLOR);
    DrawText(second_tens, minute_margin + digit_gap * 3, ypos, TIME_FONT_SIZE, FONT_COLOR);
    DrawText(second_ones, minute_margin + digit_gap * 4, ypos, TIME_FONT_SIZE, FONT_COLOR);
}

