#ifndef INCLUDED_constants_h
#define INCLUDED_constants_h

#include <raylib.h>

#define WIDTH 400
#define HEIGHT 400

#define TIME_FONT_SIZE 100
#define LABEL_FONT_SIZE 25

#define TIME_TOP_PADDING 60
#define LABEL_BOTTOM_PADDING 40

#define FONT_COLOR ((Color) { \
    .r = 200, \
    .g = 255, \
    .b = 200, \
    .a = 255 \
})

#define BUTTON_COLOR ((Color){\
    .r = 64,\
    .g = 128,\
    .b = 0,\
    .a = 255,\
})

#define BUTTON_HOVER_COLOR ((Color){\
    .r = 64,\
    .g = 128,\
    .b = 64,\
    .a = 255,\
})

#define BUTTON_PRESS_COLOR ((Color){\
    .r = 0,\
    .g = 128,\
    .b = 64,\
    .a = 255,\
})

#endif
