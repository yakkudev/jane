#include "entity.h"
#include "component.h"
#include <stdexcept>

Entity::Entity(sf::RenderTarget* target) {
    this->target = target;
}

Entity::~Entity() {
    for (auto& component : components) {
        delete component;
    }
}

bool Entity::hasComponent(Component* component) {
    return std::find(components.begin(), components.end(), component) != components.end();
}

Entity* Entity::addComponent(Component* component) {
    if (hasComponent(component)) {
        throw std::runtime_error("Entity already has component");
        return nullptr;
    }

    components.push_back(component);
    component->setEntity(this);

    return this;
}

void Entity::removeComponent(Component* component) {
    components.erase(std::remove(components.begin(), components.end(), component), components.end());
}

void Entity::update() {
    for (auto& component : components) {
        component->update();
    }
}

void Entity::render() {
    for (auto& component : components) {
        component->render(target);
    }
}