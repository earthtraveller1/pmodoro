#include <string.h>

#include "vector-math.h"
#include "constants.h"

#include "buttons.h"

struct button new_triangle_button(Vector2 pos, bool upside_down) {
    return (struct button) {
        .pos = pos,
        .size = (Vector2) { 20.0, 10.0 },
        .color = BUTTON_COLOR,
        .is_triangle = true,
        .is_upside_down = upside_down,
        .label = NULL,
    };
}

bool is_hovered(Vector2 pos, Vector2 size) {
    Vector2 mouse_pos = GetMousePosition();

    return 
        (mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + size.x) && 
        (mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + size.y); 
}

bool button_pressed(const struct button* button) {
    return IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && is_hovered(button->pos, button->size);
}

void draw_button(const struct button* button) {
    Color color = button->color;

    if (is_hovered(button->pos, button->size)) {
        color = BUTTON_HOVER_COLOR;

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            color = BUTTON_PRESS_COLOR;
        }
    }

    if (button->is_triangle) {
        Vector2 a, b, c;

        if (button->is_upside_down) {
            c = (Vector2) { button->pos.x, button->pos.y };
            b = (Vector2) { button->pos.x + button->size.x, button->pos.y };
            a = (Vector2) { button->pos.x + button->size.x / 2, button->pos.y + button->size.y };
        } else {
            a = (Vector2) { button->pos.x, button->pos.y + button->size.y };
            b = (Vector2) { button->pos.x + button->size.x, button->pos.y + button->size.y };
            c = (Vector2) { button->pos.x + button->size.x / 2, button->pos.y};
        }

        DrawTriangle(a, b, c, color);
    } else {
        DrawRectangleV(button->pos, button->size, color);
    }

    if (button->label) {
        int text_width = MeasureText(button->label, LABEL_FONT_SIZE);
        int label_x = button->pos.x + (button->size.x - text_width) / 2;
        int label_y = button->pos.y + (button->size.y - LABEL_FONT_SIZE) / 2;
        DrawText(button->label, label_x, label_y, LABEL_FONT_SIZE, FONT_COLOR);
    }
}

struct time_buttons new_time_buttons(Vector2 pos) {
    struct time_buttons buttons;
    memset(&buttons, 0, sizeof(buttons));

    const float minute_margin = 90.0;
    const float second_margin = minute_margin + 140.0;
    const float digit_gap = 60.0;
    const float v_padding = 10.0;
    const float v_font_size = 80.0;

    buttons.minute_tens_inc = new_triangle_button(VEC_ADD(pos, VEC(minute_margin, -v_padding)), false);
    buttons.minute_tens_dec = new_triangle_button(VEC_ADD(pos, VEC(minute_margin, v_font_size + v_padding)), true);

    buttons.minute_ones_inc = new_triangle_button(VEC_ADD(pos, VEC(minute_margin + digit_gap, -v_padding)), false);
    buttons.minute_ones_dec = new_triangle_button(VEC_ADD(pos, VEC(minute_margin + digit_gap, v_font_size + v_padding)), true);

    buttons.second_tens_inc = new_triangle_button(VEC_ADD(pos, VEC(second_margin, -v_padding)), false);
    buttons.second_tens_dec = new_triangle_button(VEC_ADD(pos, VEC(second_margin, v_font_size + v_padding)), true);

    buttons.second_ones_inc = new_triangle_button(VEC_ADD(pos, VEC(second_margin + digit_gap, -v_padding)), false);
    buttons.second_ones_dec = new_triangle_button(VEC_ADD(pos, VEC(second_margin + digit_gap, v_font_size + v_padding)), true);

    return buttons;
}

void draw_time_buttons(const struct time_buttons* time_buttons) {
    draw_button(&time_buttons->minute_tens_inc);
    draw_button(&time_buttons->minute_tens_dec);
    draw_button(&time_buttons->minute_ones_inc);
    draw_button(&time_buttons->minute_ones_dec);

    draw_button(&time_buttons->second_tens_inc);
    draw_button(&time_buttons->second_tens_dec);
    draw_button(&time_buttons->second_ones_inc);
    draw_button(&time_buttons->second_ones_dec);
}

void update_time(const struct time_buttons* time_buttons, struct time* time) {
    if (button_pressed(&time_buttons->minute_tens_inc)) time_inc_mins(time, 10);
    if (button_pressed(&time_buttons->minute_tens_dec)) time_dec_mins(time, 10);
    if (button_pressed(&time_buttons->minute_ones_inc)) time_inc_mins(time, 1);
    if (button_pressed(&time_buttons->minute_ones_dec)) time_dec_mins(time, 1);

    if (button_pressed(&time_buttons->second_tens_inc)) time_inc_secs(time, 10);
    if (button_pressed(&time_buttons->second_tens_dec)) time_dec_secs(time, 10);
    if (button_pressed(&time_buttons->second_ones_inc)) time_inc_secs(time, 1);
    if (button_pressed(&time_buttons->second_ones_dec)) time_dec_secs(time, 1);
}
