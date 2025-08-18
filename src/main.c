#include <raylib.h>

#include <stdbool.h>

#include "vector-math.h"
#include "buttons.h"
#include "constants.h"

void draw_centered_text(const char* text, int ypos, int font_size) {
    int text_width = MeasureText(text, font_size);
    Vector2 position = VEC((WIDTH - text_width) / 2.0, ypos);
    DrawTextEx(GetFontDefault(), text, position, font_size, 10, FONT_COLOR);
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
        .color = BUTTON_COLOR,
        .is_triangle = false,
        .is_upside_down = false,
        .label = "Start"
    };

    struct button save_button = {
        .pos = { WIDTH - 65, 0.0 },
        .size = { 65, 25 },
        .color = BUTTON_COLOR_2,
        .is_triangle = false,
        .is_upside_down = false,
        .label = "Save"
    };

    struct button load_button  = {
        .pos = { 0.0, 0.0 },
        .size = { 65, 25 },
        .color = BUTTON_COLOR_2,
        .is_triangle = false,
        .is_upside_down = false,
        .label = "Load"
    };

    struct time_buttons work_time_buttons = new_time_buttons(VEC(0.0, TIME_TOP_PADDING));
    struct time_buttons rest_time_buttons = new_time_buttons(VEC(0.0, TIME_TOP_PADDING * 2 + TIME_FONT_SIZE));

    while (!WindowShouldClose()) {
        update_time(&work_time_buttons, &work);
        update_time(&rest_time_buttons, &rest);

        BeginDrawing();
        ClearBackground(GetColor(0x0f0f0fff));

        draw_centered_text("Work", TIME_TOP_PADDING - LABEL_BOTTOM_PADDING, LABEL_FONT_SIZE);
        draw_time(&work, TIME_TOP_PADDING);

        draw_centered_text("Rest", TIME_TOP_PADDING * 2 + TIME_FONT_SIZE - LABEL_BOTTOM_PADDING, LABEL_FONT_SIZE);
        draw_time(&rest, TIME_TOP_PADDING * 2 + TIME_FONT_SIZE);

        draw_button(&save_button);
        draw_button(&start_button);
        draw_button(&load_button);

        draw_time_buttons(&work_time_buttons);
        draw_time_buttons(&rest_time_buttons);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
