#include <raylib.h>

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "vector-math.h"
#include "buttons.h"
#include "constants.h"

// Also, for the save format:
// work_time.minutes - 4 bytes
// work_time.seconds - 4 bytes
// rest_time.minutes - 4 bytes
// rest_time.seconds - 4 bytes

bool save_times(struct time work_time, struct time rest_time) {
    const char* home = getenv("HOME");
    const char* file_name = "/.pmodoro";
    char* path = malloc(strlen(home) + strlen(file_name) + 1);

    // THIS IS PERFECTLY SAFE!!!
    // WE HAVE ALREADY ENSURED ALL THE LENGTHS ARE CORRECT BEFOREHAND!!!
    // DO NOT WORRY!!!
    strcpy(path, home);
    strcat(path, file_name);

    FILE* target_file = fopen(path, "w");
    if (target_file == NULL) {
        return false;
    }

    fwrite(&work_time.minutes, sizeof(uint32_t), 1, target_file);
    if (ferror(target_file) != 0) return false;
    fwrite(&work_time.seconds, sizeof(uint32_t), 1, target_file);
    if (ferror(target_file) != 0) return false;
    fwrite(&rest_time.minutes, sizeof(uint32_t), 1, target_file);
    if (ferror(target_file) != 0) return false;
    fwrite(&work_time.seconds, sizeof(uint32_t), 1, target_file);
    if (ferror(target_file) != 0) return false;

    fclose(target_file);

    return true;
}

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

enum page_enum update_main_page(struct main_page* main_page, struct time* work, struct time* rest) {
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

    if (button_pressed(&main_page->start_button)) {
        return pages_work;
    }

    return pages_main;
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
        .pos = VEC((WIDTH - button_size.x) / 2, HEIGHT - 100.0),
        .size = button_size,
        .color = BUTTON_COLOR_2,
        .is_triangle = false,
        .is_upside_down = false,
        .label = "Stop"
    };

    return timer_page;
}

enum page_enum update_timer_page(struct timer_page* timer_page, struct time work, struct time rest) {
    assert(page == pages_rest || page == pages_work);

    BeginDrawing();
    ClearBackground(GetColor(0x0f0f0fff));

    double target_time = 0.0;
    
    if (page == pages_rest) {
        draw_centered_text("Rest", 50, 50);
        target_time = timer_page->start_time + time_to_secs(rest);
    } else {
        draw_centered_text("Work", 50, 50);
        target_time = timer_page->start_time + time_to_secs(work);
    }

    draw_button(&timer_page->stop_button);

    double remaining_time = target_time - GetTime();

    if (remaining_time >= 0.0) {
        struct time displayed_time = secs_to_time(remaining_time);
        draw_time(&displayed_time, 150.0f);
    }

    EndDrawing();

    if (remaining_time < 0.0) {
        if (page == pages_work) {
            page = pages_rest;
        } else if (page == pages_rest) {
            page = pages_work;
        }
        
        timer_page->start_time = GetTime();
    }

    if (button_pressed(&timer_page->stop_button)) {
        timer_page->start_time = 0;
        return pages_main;
    }

    return page;
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
            page = update_main_page(&main_page, &work, &rest);
            if (page == pages_work) {
                timer_page.start_time = GetTime();
            }
        } else if (page == pages_rest || page == pages_work) {
            page = update_timer_page(&timer_page, work, rest);
        }
    }

    CloseWindow();
    return 0;
}
