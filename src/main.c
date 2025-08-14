#include <raylib.h>

#include <stdio.h>
#include <stdbool.h>

#include "vector-math.h"
#include "buttons.h"
#include "constants.h"

void draw_centered_text(const char* text, int ypos, int font_size) {
    int text_width = MeasureText(text, font_size);
    DrawText(text, (WIDTH - text_width) / 2, ypos, font_size, FONT_COLOR);
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
        update_time(&work_time_buttons, &work);

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
