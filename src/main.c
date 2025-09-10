#include <raylib.h>

#include <stdbool.h>
#include <string.h>
#include <assert.h>

#include "vector-math.h"
#include "buttons.h"
#include "constants.h"

enum page_enum {
    pages_main,
    pages_work,
    pages_rest,
} page = pages_main;

struct main_page {
    struct button start_button;
    struct button save_button;
    struct button load_button;
    
    struct time_buttons work_time_buttons;
    struct time_buttons rest_time_buttons;
};

void draw_centered_text(const char* text, int ypos, int font_size);

struct main_page new_main_page(void) {
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


    return ( struct main_page ) {
        start_button,
        save_button,
        load_button,

        work_time_buttons,
        rest_time_buttons,
    };
}

void update_main_page(struct main_page* main_page, struct time* work, struct time* rest) {
    update_time(&main_page->work_time_buttons, work);
    update_time(&main_page->rest_time_buttons, rest);

    BeginDrawing();
    ClearBackground(GetColor(0x0f0f0fff));

    draw_centered_text("Work", TIME_TOP_PADDING - LABEL_BOTTOM_PADDING, LABEL_FONT_SIZE);
    draw_time(work, TIME_TOP_PADDING);

    draw_centered_text("Rest", TIME_TOP_PADDING * 2 + TIME_FONT_SIZE - LABEL_BOTTOM_PADDING, LABEL_FONT_SIZE);
    draw_time(rest, TIME_TOP_PADDING * 2 + TIME_FONT_SIZE);

    draw_button(&main_page->save_button);
    draw_button(&main_page->start_button);
    draw_button(&main_page->load_button);

    draw_time_buttons(&main_page->work_time_buttons);
    draw_time_buttons(&main_page->rest_time_buttons);

    EndDrawing();
}

struct timer_page {
    struct button stop_button;
    double start_time;
};

struct timer_page new_timer_page(void) {
    struct timer_page timer_page;
    memset(&timer_page, 0, sizeof(timer_page));

    Vector2 button_size = VEC(150.0f, 50.0f);

    timer_page.stop_button = (struct button) {
        .pos = VEC(( button_size.x - WIDTH ) / 2, HEIGHT - 100.0),
        .size = button_size,
        .color = BUTTON_COLOR_2,
        .is_triangle = false,
        .is_upside_down = false,
        .label = "Stop"
    };

    return timer_page;
}

void update_timer_page(struct timer_page* timer_page, struct time work, struct time rest) {
    assert(page == pages_rest || page == pages_work);

    BeginDrawing();

    draw_button(&timer_page->stop_button);

    EndDrawing();
}

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

    struct main_page main_page = new_main_page();
    struct timer_page timer_page = new_timer_page();

    while (!WindowShouldClose()) {
        if (page == pages_main) {
            update_main_page(&main_page, &work, &rest);
        } else if (page == pages_rest || page == pages_work) {
            update_timer_page(&timer_page, work, rest);
        }
    }

    CloseWindow();
    return 0;
}
