#include "game.h"
#include "input_manager.h"
#include "scene.h"
#include "components/transform.h"
#include "components/camera.h"
#include <iostream>

f32 Game::deltaTime = 0.0f;
f32 Game::staticDeltaTime = 0.0f;
Game* Game::game = nullptr;
Window* Game::window = nullptr;
sf::View* Game::view = nullptr;
sf::RenderTexture* Game::uiTexture;

Game::Game(u32 width, u32 height, const std::string& title) {
    isRunning = false;
    window = new Window{ sf::VideoMode{ width, height }, title };
    view = new sf::View{ window->getDefaultView() };
    game = this;
    uiTexture = new sf::RenderTexture;
    uiTexture->create(width, height);

    window->setFramerateLimit(120);
}

Game::~Game() {
    clean();
}

void Game::addEntity(Entity* entity) {
    entityBuffer.push_back(entity);
}

void Game::addEntity(std::vector<Component*> components) {
    Entity* entity = new Entity(window);
    for (auto& component : components) {
        entity->addComponent(component);
    }
    addEntity(entity);
}

void Game::addUIEntity(std::vector<Component*> components) {
    Entity* entity = new Entity(window);
    entity->isUI = true;
    for (auto& component : components) {
        entity->addComponent(component);
    }
    addEntity(entity);
}

void Game::playScene(Scene* scene) {
    for (auto& entity : scene->entities) {
        addEntity(entity);
    }
}

void Game::init() {
    AssetManager::init();
    InputManager::init(window);

    SceneManager::init();
}

void Game::run() {
    sf::Clock gameClock;
    sf::Clock deltaClock;
    deltaTime = 0.0f;

    isRunning = true;

    playScene(SceneManager::scenes[2]);
    addEntity({ new GC_Transform(), new GC_Camera() });
    pushEntityBuffer();

    // Init entities
    for (auto& entity : entities) {
        entity->init();
    }

    // Update loop
    for (;;) {
        handleEvents();
        if (!running()) break;

        pushEntityBuffer();

        // Update
        update();
        if (gameClock.getElapsedTime().asSeconds() >= (1.0f / 60.0f)) {
            fixedUpdate();
            staticDeltaTime = gameClock.getElapsedTime().asSeconds();
            gameClock.restart();
        }

        // Render
        window->clear();
        render();
        drawUI();
        window->display();

        // Calculate delta time
        Game::deltaTime = deltaClock.getElapsedTime().asSeconds();
        deltaClock.restart();
    }
}

void Game::pushEntityBuffer() {
    for (auto& entity : entityBuffer) {
        entities.push_back(entity);
    }
    entityBuffer.clear();
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
        if (!entity->isUI)
            entity->render();
    }
}

void Game::fixedUpdate() {
    for (auto& entity : entities) {
        entity->fixedUpdate();
    }
}

void Game::drawUI() {
    uiTexture->clear(sf::Color::Transparent);
    for (auto& entity : entities) {
        if (entity->isUI) {
            entity->render();
        }
    }
    uiTexture->display();
    sf::Sprite sprite{ uiTexture->getTexture() };
    window->setView(window->getDefaultView());
    window->draw(sprite);
    window->setView(*view);
}

void Game::killEntity(Entity* entity) {
    entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
    delete entity;
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

Game* Game::getGame() {
    return game;
}

sf::RenderTexture* Game::getUITexture() {
    return uiTexture;
}