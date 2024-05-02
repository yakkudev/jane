#pragma once

#include "entity.h"
#include "types.h"
#include "asset_manager.h"
#include "component_manager.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Game {
private:

    template <typename T>
    static void runTest(int testValue) {
        if (ComponentManager::getComponentID<T>() == testValue) {
            std::cout << "Test passed!" << std::endl;
        }
        else {
            std::cout << "Test failed!" << std::endl;
            throw std::runtime_error("Test failed!");
        }
    }

    bool isRunning;
    Window* window;
    sf::View view;
    std::vector<Entity*> entities;

public:
    Game(u32 width, u32 height, const std::string& title);
    ~Game();
    void run();

    void init();
    void update();
    void render();
    void handleEvents();
    void clean();
    bool running() { return isRunning; }

    static f32 deltaTime;
};