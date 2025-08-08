#include <raylib.h>

#include <stdio.h>

#define WIDTH 400
#define HEIGHT 400

int main(void) {
    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(WIDTH, HEIGHT, "PMOdoro");

    while (!WindowShouldClose()) {
        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
