#pragma once

#include <SFML/Graphics.hpp>
#include "types.h"

class InputManager {
private:
    static f32 mouseWheel;
    static Vec2i mousePosition;
    static Vec2i mouseDelta;
    static Window* window;
public:
    static void init(Window* window);

    static void update();

    static bool getKey(KeyCode key);
    static bool getKeyDown(KeyCode key);
    static bool getKeyUp(KeyCode key);

    static bool getMouseButton(MouseButton button);
    static bool getMouseButtonDown(MouseButton button);
    static bool getMouseButtonUp(MouseButton button);

    static void setMouseWheel(f32 value);
    static f32 getMouseWheel();

    static Vec2i getMousePosition();
    static Vec2i getMouseDelta();
    static Vec2 getMouseWorldPosition();
};