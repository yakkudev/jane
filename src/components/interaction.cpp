#include "interaction.h"
#include "input_manager.h"
#include "entity.h"
#include "transform.h"
#include <iostream>

GC_Interaction::GC_Interaction() {
    require<GC_Transform>();
}

void GC_Interaction::registerListener(std::function<void()> listener, Type type) {
    listeners.push_back(std::make_pair(listener, type));
}

void GC_Interaction::init() {
    transform = entity->getComponent<GC_Transform>();
}

void GC_Interaction::update() {
    auto mousePos = InputManager::getMouseWorldPosition();
    auto bounds = sf::Rect(
        transform->position.x - transform->scale.x / 2,
        transform->position.y - transform->scale.y / 2,
        transform->scale.x,
        transform->scale.y
    );

    if (bounds.contains(mousePos)) {
        for (auto& listener : listeners) {
            if (listener.second == Type::MOUSE_UP
                && InputManager::getMouseButtonUp(MouseButton::Left)) {
                listener.first();
            }

            if (listener.second == Type::MOUSE_DOWN
                && InputManager::getMouseButtonDown(MouseButton::Left)) {
                listener.first();
            }
        }
    }

}