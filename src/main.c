#include <raylib.h>

#include <stdio.h>
#include <string.h>

#define WIDTH 400
#define HEIGHT 400

#define TIME_FONT_SIZE 100
#define TIME_TOP_PADDING 50

struct time {
    int minutes;
    int seconds;
};

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

        snprintf(text_buf, 512, "%02d:%02d", work.minutes, work.seconds);
        text_width = MeasureText(text_buf, TIME_FONT_SIZE);
        DrawText(
            text_buf, 
            (WIDTH - text_width) / 2, 
            TIME_TOP_PADDING, 
            TIME_FONT_SIZE, 
            (Color){ .r = 200, .g = 255, .b = 200, .a = 255}
        );

        snprintf(text_buf, 512, "%02d:%02d", rest.minutes, rest.seconds);
        text_width = MeasureText(text_buf, TIME_FONT_SIZE);
        DrawText(
            text_buf, 
            (WIDTH - text_width) / 2, 
            TIME_TOP_PADDING * 2 + TIME_FONT_SIZE, 
            TIME_FONT_SIZE, 
            (Color){ .r = 200, .g = 255, .b = 200, .a = 255}
        );

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
