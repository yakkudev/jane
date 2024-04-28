#include "entity.h"

Entity::~Entity() {
    for (auto& component : components) {
        delete component;
    }
}

void Entity::addComponent(Component* component) {
    components.push_back(component);
}

void Entity::removeComponent(Component* component) {
    // Remove the component from the vector
    components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

void Entity::update() {
    for (auto& component : components) {
        component->update();
    }
}

void Entity::render() {
    for (auto& component : components) {
        component->render();
    }
}