#pragma once

#include "entity.h"
#include "types.h"
#include "asset_manager.h"
#include <SFML/Graphics.hpp>

class Game {
private:

    bool isRunning;
    sf::RenderWindow* window;
    std::vector<Entity*> entities;

    AssetManager assetManager;

public:
    Game(u32 width, u32 height, const std::string& title);
    ~Game();
    void run();

    void update();
    void render();
    void handleEvents();
    void clean();
    bool running() { return isRunning; }

};