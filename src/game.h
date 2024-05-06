#pragma once

#include "entity.h"
#include "types.h"
#include "asset_manager.h"
#include "component_manager.h"
#include "scene.h"
#include <iostream>
#include <SFML/Graphics.hpp>

class Game {
private:

    static Window* window;
    static sf::View* view;
    bool isRunning;
    std::vector<Entity*> entities;

public:
    Game(u32 width, u32 height, const std::string& title);
    ~Game();
    void run();

    void init();
    void update();
    void fixedUpdate();
    void render();
    void handleEvents();
    void clean();
    bool running() { return isRunning; }

    void addEntity(std::vector<Component*> components);
    void playScene(Scene* scene);

    static Window* getWindow();
    static sf::View* getView();

    static f32 deltaTime;
    static f32 staticDeltaTime;
};