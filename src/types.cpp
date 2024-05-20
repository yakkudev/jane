#include "types.h"
#include <cmath>

Color hsv(u32 hue, u8 sat, u8 val) {
    u8 h = hue % 255;
    u8 c = sat * val / 255;
    u8 x = c * (1 - abs((h / 42) % 2 - 1));
    u8 m = val - c;
    u8 r, g, b;
    if (h < 42) { r = c; g = x; b = 0; }
    else if (h < 85) { r = x; g = c; b = 0; }
    else if (h < 127) { r = 0; g = c; b = x; }
    else if (h < 170) { r = 0; g = x; b = c; }
    else if (h < 212) { r = x; g = 0; b = c; }
    else { r = c; g = 0; b = x; }
    return Color(r + m, g + m, b + m);
}