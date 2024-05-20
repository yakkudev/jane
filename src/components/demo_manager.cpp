#include "demo_manager.h"
#include "demo_attractor.h"
#include "game.h"
#include "entity.h"
#include "input_manager.h"

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
        spawnMass += 1;
    }
    else if (InputManager::getKey(KeyCode::S)) {
        if (spawnMass > 1)
            spawnMass -= 1;
    }

}

void GC_DemoManager::render(sf::RenderTarget* target) {
    Vec2 diff = holdStart - holdEnd;
    if (InputManager::getMouseButtonUp(MouseButton::Right)) {

        Entity* entity = new Entity(target);
        entity->addComponent(new GC_DemoAttractor(spawnMass, sqrtf(spawnMass), Vec2(diff.x * 0.2, diff.y * 0.2)));
        entity->addComponent(new GC_Transform(holdStart.x, holdStart.y));
        entity->init();
        Game::getGame()->addEntity(entity);

        holdStart = Vec2(0, 0);
        holdEnd = Vec2(0, 0);
    }
    if (holdStart == Vec2(0, 0)) return;

    sf::Vertex line[] = {
        sf::Vertex(Vec2(holdStart.x, holdStart.y)),
        sf::Vertex(holdStart + diff)
    };

    line[0].color = hsv(spawnMass, 255, 255);
    target->draw(line, 2, sf::Lines);

    f32 radius = sqrtf(spawnMass);
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(holdStart);
    circle.setFillColor(hsv(spawnMass, 255, 255));
    target->draw(circle);

    sf::Text text;
    text.setFont(*AssetManager::getFont("ProggyClean"));
    text.setString(
        "Mass: " + std::to_string((int)spawnMass)
        + "\nRadius: " + std::to_string((int)radius)
    );
    text.setCharacterSize(16);

    text.setPosition(holdStart + Vec2(0, -radius - 20));
    text.setFillColor(sf::Color::White);
    target->draw(text);
}