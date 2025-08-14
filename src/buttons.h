#ifndef INCLUDED_buttons_h
#define INCLUDED_buttons_h

#include <raylib.h>

#include "time.h"
#include "constants.h"

struct button {
    Vector2 pos;
    Vector2 size;
    Color color;
    bool is_triangle;
    bool is_upside_down;
    const char* label;
};

struct time_buttons {
    struct button minute_tens_inc;
    struct button minute_tens_dec;
    struct button minute_ones_inc;
    struct button minute_ones_dec;

    struct button second_tens_inc;
    struct button second_tens_dec;
    struct button second_ones_inc;
    struct button second_ones_dec;
};

struct button new_triangle_button(Vector2 pos, bool upside_down);

bool is_hovered(Vector2 pos, Vector2 size);

bool button_pressed(const struct button* button);

void draw_button(const struct button* button);

struct time_buttons new_time_buttons(Vector2 pos);

void draw_time_buttons(const struct time_buttons* time_buttons);

void update_time(const struct time_buttons* time_buttons, struct time* time);

#endif


