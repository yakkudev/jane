#include "demo_manager.h"
#include "demo_attractor.h"
#include "demo_attractor_action.h"
#include "game.h"
#include "entity.h"
#include "input_manager.h"
#include "text.h"
#include "sprite.h"
#include "transform.h"
#include "interaction.h"
#include "scene.h"
#include <cmath>

GC_DemoManager::GC_DemoManager() {}

void GC_DemoManager::init() {
}

void GC_DemoManager::update() {
    if (InputManager::getMouseButtonDown(MouseButton::Right)) {
        holdStart = InputManager::getMouseWorldPosition();
    }

    if (InputManager::getMouseButton(MouseButton::Right)) {
        holdEnd = InputManager::getMouseWorldPosition();
    }

    if (InputManager::getKey(KeyCode::W)) {
        spawnMass += 2;
    }
    else if (InputManager::getKey(KeyCode::S)) {
        if (spawnMass > 2)
            spawnMass -= 2;
    }

    if (InputManager::getKeyDown(KeyCode::R)) {
        Game::getGame()->playScene(SceneManager::scenes[2]);
    }
}

void GC_DemoManager::render(sf::RenderTarget* target) {
    Vec2 diff = this->holdStart - this->holdEnd;
    if (InputManager::getMouseButtonUp(MouseButton::Right)) {

        Entity* entity = new Entity(target);
        entity->addComponent(new GC_DemoAttractor(spawnMass, 0.0, Vec2(diff.x * 0.2, diff.y * 0.2)))
            ->addComponent(new GC_Transform(holdStart.x, holdStart.y))
            ->addComponent(new GC_DemoAttractorAction())
            ->addComponent(new GC_Interaction(3));
        Game::getGame()->addEntity(entity);

        holdStart = Vec2(0, 0);
        holdEnd = Vec2(0, 0);
    }
    if (holdStart == Vec2(0, 0)) return;

    sf::Vertex line[] = {
        sf::Vertex(Vec2(holdStart.x, holdStart.y)),
        sf::Vertex(holdStart + diff)
    };

    line[0].color = hsv(spawnMass, 1.0, 1.0);
    target->draw(line, 2, sf::Lines);

    f32 radius = sqrt(spawnMass);
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(holdStart);
    circle.setFillColor(hsv(spawnMass, 1.0, 1.0));
    target->draw(circle);

    sf::Text text;
    text.setFont(*AssetManager::getFont("ProggyClean"));
    text.setString(
        "Mass: " + std::to_string((int)spawnMass)
        + "\nRadius: " + std::to_string((int)radius)
    );
    text.setCharacterSize(32);

    text.setPosition(holdStart + Vec2(0, -radius - 20));
    text.setFillColor(sf::Color::White);
    target->draw(text);
}