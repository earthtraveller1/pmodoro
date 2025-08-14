#include <raylib.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "vector-math.h"

#define WIDTH 400
#define HEIGHT 400

#define TIME_FONT_SIZE 100
#define LABEL_FONT_SIZE 25

#define TIME_TOP_PADDING 60
#define LABEL_BOTTOM_PADDING 40

const Color FONT_COLOR = { 
    .r = 200, 
    .g = 255, 
    .b = 200, 
    .a = 255
};

const Color BUTTON_COLOR = {
    .r = 64,
    .g = 128,
    .b = 0,
    .a = 255,
};

const Color BUTTON_HOVER_COLOR = {
    .r = 64,
    .g = 128,
    .b = 64,
    .a = 255,
};

const Color BUTTON_PRESS_COLOR = {
    .r = 0,
    .g = 128,
    .b = 64,
    .a = 255,
};

struct time {
    int minutes;
    int seconds;
};

void draw_centered_text(const char* text, int ypos, int font_size) {
    int text_width = MeasureText(text, font_size);
    DrawText(text, (WIDTH - text_width) / 2, ypos, font_size, FONT_COLOR);
}

struct button {
    Vector2 pos;
    Vector2 size;
    bool is_triangle;
    bool is_upside_down;
    const char* label;
};

struct button new_triangle_button(Vector2 pos, bool upside_down) {
    return (struct button) {
        .pos = pos,
        .size = (Vector2) { 20.0, 10.0 },
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
    Color color = BUTTON_COLOR;

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

int main(void) {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(WIDTH, HEIGHT, "PMOdoro");

    SetTargetFPS(60);

    struct time work = {25, 0};
    struct time rest = {5, 0};

    struct button start_button = {
        .pos = { (WIDTH - 150) / 2.0, 325 },
        .size = { 150, 50 },
        .is_triangle = false,
        .is_upside_down = false,
        .label = "Start"
    };

    struct time_buttons work_time_buttons = new_time_buttons(VEC(0.0, TIME_TOP_PADDING));

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GetColor(0x0f0f0fff));

        char text_buf[512];

        draw_centered_text("Work", TIME_TOP_PADDING - LABEL_BOTTOM_PADDING, LABEL_FONT_SIZE);

        snprintf(text_buf, 512, "%02d:%02d", work.minutes, work.seconds);
        draw_centered_text(text_buf, TIME_TOP_PADDING, TIME_FONT_SIZE);

        draw_centered_text("Rest", TIME_TOP_PADDING * 2 + TIME_FONT_SIZE - LABEL_BOTTOM_PADDING, LABEL_FONT_SIZE);

        snprintf(text_buf, 512, "%02d:%02d", rest.minutes, rest.seconds);
        draw_centered_text(text_buf, TIME_TOP_PADDING * 2 + TIME_FONT_SIZE, TIME_FONT_SIZE);

        draw_button(&start_button);

        draw_time_buttons(&work_time_buttons);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
