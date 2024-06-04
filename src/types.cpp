#include "types.h"
#include <cmath>

Color hsv(f32 hue, f32 sat, f32 val) {
    hue = fmod(hue, 360);
    sat = std::clamp(sat, 0.0f, 1.0f);
    val = std::clamp(val, 0.0f, 1.0f);

    // https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
    f32 c = sat * val;
    f32 h = hue / 60;
    f32 x = c * (1 - std::abs(fmod(h, 2) - 1));
    f32 m = val - c;

    f32 r, g, b;
    if (h >= 0 && h < 1) {
        r = c;
        g = x;
        b = 0;
    }
    else if (h >= 1 && h < 2) {
        r = x;
        g = c;
        b = 0;
    }
    else if (h >= 2 && h < 3) {
        r = 0;
        g = c;
        b = x;
    }
    else if (h >= 3 && h < 4) {
        r = 0;
        g = x;
        b = c;
    }
    else if (h >= 4 && h < 5) {
        r = x;
        g = 0;
        b = c;
    }
    else if (h >= 5 && h < 6) {
        r = c;
        g = 0;
        b = x;
    }
    else {
        r = 0;
        g = 0;
        b = 0;
    }

    return Color((r + m) * 255, (g + m) * 255, (b + m) * 255);

}

f32 magnitude(Vec2 v) {
    return sqrt(v.x * v.x + v.y * v.y);
}

Vec2 normalized(Vec2 v) {
    f32 mag = magnitude(v);
    return Vec2(v.x / mag, v.y / mag);
}

f32 dot(Vec2 a, Vec2 b) {
    return a.x * b.x + a.y * b.y;
}

Vec2 operator*(const Vec2& v, const f32& s) {
    return Vec2(v.x * s, v.y * s);
}