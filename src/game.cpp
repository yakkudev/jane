#include "game.h"
#include "input_manager.h"
#include "components/transform.h"
#include "components/sprite.h"
#include "components/text.h"
#include <iostream>

f32 Game::deltaTime = 0.0f;

Game::Game(u32 width, u32 height, const std::string& title) {
    isRunning = false;
    window = new Window{ sf::VideoMode{ width, height }, title };
}

Game::~Game() {
    clean();
}

void Game::init() {
    AssetManager::init();
    InputManager::init(window);

    u32 test2 = ComponentManager::registerComponent<SpriteComponent>();
    u32 test = ComponentManager::registerComponent<TransformComponent>();
    runTest<TransformComponent>(test);
    runTest<SpriteComponent>(test2);

    view = window->getDefaultView();
    view.setCenter(0, 0);
}

void Game::run() {
    sf::Clock gameClock;
    sf::Time tick;
    deltaTime = 0.0f;

    isRunning = true;

    entities.push_back(
        (new Entity(window))
        ->addComponent(new TransformComponent())
        ->addComponent(new SpriteComponent("sheldon"))
    );

    entities.push_back(
        (new Entity(window))
        ->addComponent(new TransformComponent())
        ->addComponent(new TextComponent("ProggyClean", "Hello, World!"))
    );

    for (;;) {
        handleEvents();
        if (!running()) break;

        Game::deltaTime = (tick - gameClock.getElapsedTime()).asSeconds();
        update();

        window->clear();
        window->setView(view);
        render();
        window->display();

        tick = gameClock.getElapsedTime();
    }
}

void Game::handleEvents() {
    for (auto event = sf::Event{}; window->pollEvent(event);) {
        if (event.type == sf::Event::Closed) {
            this->isRunning = false;
            window->close();
            return;
        }

        if (event.type == sf::Event::Resized) {
            view.setSize(event.size.width, event.size.height);
        }
    }
}

void Game::update() {
    InputManager::update();
    for (auto& entity : entities) {
        entity->update();
    }
}

void Game::render() {
    for (auto& entity : entities) {
        entity->render();
    }
}

void Game::clean() {
    AssetManager::clean();

    for (auto& entity : entities) {
        delete entity;
    }
    delete window;
}