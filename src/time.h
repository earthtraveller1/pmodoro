#ifndef INCLUDED_time_h
#define INCLUDED_time_h

typedef struct Vector2 Vector2;

struct time {
    int minutes;
    int seconds;
};

void time_inc_mins(struct time* time, unsigned int mins); 

void time_dec_mins(struct time* time, unsigned int mins);

void time_inc_secs(struct time* time, unsigned int secs); 

void time_dec_secs(struct time* time, unsigned int secs);

void draw_time(const struct time* time, float ypos);

#endif
