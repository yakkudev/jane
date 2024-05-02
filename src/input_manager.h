#pragma once

#include <SFML/Graphics.hpp>
#include "types.h"

class InputManager {
private:
    static Vec2i mousePosition;
    static Vec2i mouseDelta;
    static Window* window;
public:
    static void init(Window* window);

    static void update();

    static bool getKey(sf::Keyboard::Key key);

    static bool getKeyDown(sf::Keyboard::Key key);

    static bool getKeyUp(sf::Keyboard::Key key);

    static Vec2i getMousePosition(Window* window);

    static Vec2i getMouseDelta();
};