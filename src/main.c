#include <raylib.h>

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

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
    .r = 128,
    .g = 255,
    .b = 0,
    .a = 255,
};

const Color BUTTON_HOVER_COLOR = {
    .r = 128,
    .g = 255,
    .b = 128,
    .a = 255,
};

const Color BUTTON_PRESS_COLOR = {
    .r = 0,
    .g = 255,
    .b = 128,
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
};

bool is_hovered(Vector2 pos, Vector2 size) {
    Vector2 mouse_pos = GetMousePosition();

    return 
        (mouse_pos.x >= pos.x && mouse_pos.x <= pos.x + size.x) && 
        (mouse_pos.y >= pos.y && mouse_pos.y <= pos.y + size.y); 
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
            a = (Vector2) { button->pos.x, button->pos.y };
            b = (Vector2) { button->pos.x + button->size.x, button->pos.y };
            c = (Vector2) { button->pos.x + button->size.x / 2, button->pos.y + button->size.y };
        } else {
            a = (Vector2) { button->pos.x, button->pos.y + button->size.y };
            b = (Vector2) { button->pos.x + button->size.x, button->pos.y + button->size.y };
            c = (Vector2) { button->pos.x + button->size.x / 2, button->pos.y};
        }

        DrawTriangle(a, b, c, color);
    } else {
        DrawRectangleV(button->pos, button->size, color);
    }
}

int main(void) {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(WIDTH, HEIGHT, "PMOdoro");

    struct time work = {25, 0};
    struct time rest = {5, 0};

    struct button start_button = {
        .pos = { (WIDTH - 150) / 2, 325 },
        .size = { 150, 50 },
        .is_triangle = false,
        .is_upside_down = false,
    };

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

        draw_button(&start_button);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
