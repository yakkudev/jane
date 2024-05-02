#include "input_manager.h"
#include <iostream>

f32 InputManager::mouseWheel = 0.0f;
Vec2i InputManager::mousePosition = Vec2i(0, 0);
Vec2i InputManager::mouseDelta = Vec2i(0, 0);
Window* InputManager::window = nullptr;

void InputManager::init(Window* window) {
    InputManager::window = window;
}

void InputManager::update() {
    mouseDelta = getMousePosition() - mousePosition;
    mousePosition = getMousePosition();
    mouseWheel = 0.0f;
}

bool InputManager::getKey(KeyCode key) {
    return sf::Keyboard::isKeyPressed(key);
}

bool InputManager::getKeyDown(KeyCode key) {
    static bool keys[256] = { false };
    bool isKeyDown = getKey(key) && !keys[key];
    keys[key] = getKey(key);
    return isKeyDown;
}

bool InputManager::getKeyUp(KeyCode key) {
    static bool keys[256] = { false };
    bool isKeyUp = !getKey(key) && keys[key];
    keys[key] = getKey(key);
    return isKeyUp;
}

bool InputManager::getMouseButton(MouseButton button) {
    return sf::Mouse::isButtonPressed(button);
}

bool InputManager::getMouseButtonDown(MouseButton button) {
    static bool buttons[5] = { false };
    bool isButtonDown = getMouseButton(button) && !buttons[button];
    buttons[button] = getMouseButton(button);
    return isButtonDown;
}

bool InputManager::getMouseButtonUp(MouseButton button) {
    static bool buttons[5] = { false };
    bool isButtonUp = !getMouseButton(button) && buttons[button];
    buttons[button] = getMouseButton(button);
    return isButtonUp;
}


Vec2i InputManager::getMousePosition() {
    return sf::Mouse::getPosition(*window);
}

Vec2 InputManager::getMouseWorldPosition() {
    return window->mapPixelToCoords(getMousePosition());
}

void InputManager::setMouseWheel(f32 value) {
    mouseWheel = value;
}

f32 InputManager::getMouseWheel() {
    return mouseWheel;
}

Vec2i InputManager::getMouseDelta() {
    return mouseDelta;
}