#include "game.h"
#include "entities/box.h"
#include "components/transform.h"
#include "components/sprite.h"

Game::Game(u32 width, u32 height, const std::string& title) {
    isRunning = false;
    window = new sf::RenderWindow{ sf::VideoMode{ width, height }, title };
}

Game::~Game() {
    clean();
}

void Game::run() {
    isRunning = true;

    Box* box = new Box(window);
    entities.push_back(box);

    for (;;) {
        handleEvents();
        if (!running()) break;
        update();

        window->clear();
        render();
        window->display();
    }
}

void Game::handleEvents() {
    for (auto event = sf::Event{}; window->pollEvent(event);) {
        if (event.type == sf::Event::Closed) {
            this->isRunning = false;
            window->close();
            return;
        }
    }
}

void Game::update() {
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
    for (auto& entity : entities) {
        delete entity;
    }
    delete window;
}