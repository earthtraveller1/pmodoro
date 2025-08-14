#include <stdlib.h>

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

