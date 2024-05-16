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

    static Game* game;
    static Window* window;
    static sf::View* view;
    static sf::RenderTexture* uiTexture;
    bool isRunning;
    std::vector<Entity*> entities;
    std::vector<Entity*> entityBuffer;

    void update();
    void fixedUpdate();
    void render();
    void drawUI();
    void handleEvents();
    void clean();
public:
    Game(u32 width, u32 height, const std::string& title);
    ~Game();
    void init();
    void run();

    bool running() { return isRunning; }

    void addEntity(Entity* entity);
    void addEntity(std::vector<Component*> components);
    void addUIEntity(std::vector<Component*> components);
    void killEntity(Entity* entity);
    void pushEntityBuffer();
    void playScene(Scene* scene);

    static Window* getWindow();
    static sf::View* getView();
    static Game* getGame();
    static sf::RenderTexture* getUITexture();

    static f32 deltaTime;
    static f32 staticDeltaTime;
};