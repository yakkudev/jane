#include "game.h"
#include "input_manager.h"
#include "components/transform.h"
#include "components/sprite.h"
#include "components/text.h"
#include "components/cam.h"
#include <iostream>

f32 Game::deltaTime = 0.0f;
Window* Game::window = nullptr;
sf::View* Game::view = nullptr;

Game::Game(u32 width, u32 height, const std::string& title) {
    isRunning = false;
    window = new Window{ sf::VideoMode{ width, height }, title };
    view = new sf::View{ window->getDefaultView() };

    window->setFramerateLimit(120);
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

    ComponentManager::registerComponent<TextComponent>();
    ComponentManager::registerComponent<CamComponent>();
}

void Game::run() {
    sf::Clock gameClock;
    sf::Clock deltaClock;
    deltaTime = 0.0f;

    isRunning = true;

    // This will be moved to a scene
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

    entities.push_back(
        (new Entity(window))
        ->addComponent(new TransformComponent())
        ->addComponent(new CamComponent())
    );

    // Init entities
    for (auto& entity : entities) {
        entity->init();
    }

    // Update loop
    for (;;) {
        handleEvents();
        if (!running()) break;

        update();

        window->clear();
        render();
        window->display();

        Game::deltaTime = deltaClock.getElapsedTime().asSeconds();
        deltaClock.restart();
    }
}

void Game::handleEvents() {
    for (auto event = sf::Event{}; window->pollEvent(event);) {
        if (event.type == sf::Event::Closed) {
            this->isRunning = false;
            window->close();
            return;
        }

        if (event.type == sf::Event::MouseWheelScrolled) {
            InputManager::setMouseWheel(event.mouseWheelScroll.delta);
        }
    }
}

void Game::update() {
    for (auto& entity : entities) {
        entity->update();
    }
    InputManager::update();
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

Window* Game::getWindow() {
    return window;
}

sf::View* Game::getView() {
    return view;
}