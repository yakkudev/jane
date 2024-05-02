#include "input_manager.h"
#include <iostream>

Vec2i InputManager::mousePosition = Vec2i(0, 0);
Vec2i InputManager::mouseDelta = Vec2i(0, 0);
Window* InputManager::window = nullptr;

void InputManager::init(Window* window) {
    InputManager::window = window;
}

void InputManager::update() {
    mouseDelta = getMousePosition(window) - mousePosition;
    mousePosition = getMousePosition(window);
}

bool InputManager::getKey(sf::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::getKeyDown(sf::Keyboard::Key key) {
    static bool keys[256] = { false };
    bool isKeyDown = getKey(key) && !keys[key];
    keys[key] = getKey(key);
    return isKeyDown;
}

bool InputManager::getKeyUp(sf::Keyboard::Key key) {
    static bool keys[256] = { false };
    bool isKeyUp = !getKey(key) && keys[key];
    keys[key] = getKey(key);
    return isKeyUp;
}

Vec2i InputManager::getMousePosition(Window* window) {
    return sf::Mouse::getPosition(*window);
}

Vec2i InputManager::getMouseDelta() {
    return mouseDelta;
}