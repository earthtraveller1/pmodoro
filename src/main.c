#include <raylib.h>

#include <stdio.h>
#include <string.h>

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

struct time {
    int minutes;
    int seconds;
};

void draw_centered_text(const char* text, int ypos, int font_size) {
    int text_width = MeasureText(text, font_size);
    DrawText(text, (WIDTH - text_width) / 2, ypos, font_size, FONT_COLOR);
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(WIDTH, HEIGHT, "PMOdoro");

    struct time work = {25, 0};
    struct time rest = {5, 0};

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(GetColor(0x0f0f0fff));

        char text_buf[512];
        int text_width;

        draw_centered_text("Work", TIME_TOP_PADDING - LABEL_BOTTOM_PADDING, LABEL_FONT_SIZE);

        snprintf(text_buf, 512, "%02d:%02d", work.minutes, work.seconds);
        draw_centered_text(text_buf, TIME_TOP_PADDING, TIME_FONT_SIZE);

        draw_centered_text("Rest", TIME_TOP_PADDING * 2 + TIME_FONT_SIZE - LABEL_BOTTOM_PADDING, LABEL_FONT_SIZE);

        snprintf(text_buf, 512, "%02d:%02d", rest.minutes, rest.seconds);
        draw_centered_text(text_buf, TIME_TOP_PADDING * 2 + TIME_FONT_SIZE, TIME_FONT_SIZE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
