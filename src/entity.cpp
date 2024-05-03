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

bool Entity::hasComponent(u32 componentID) {
    for (auto& component : components) {
        if (ComponentManager::getComponentID(typeid(*component)) == componentID) {
            return true;
        }
    }
    return false;
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

void Entity::fixedUpdate() {
    for (auto& component : components) {
        component->fixedUpdate();
    }
}

void Entity::render() {
    for (auto& component : components) {
        component->render(target);
    }
}

bool Entity::componentCheck() {
    for (auto& component : components) {
        for (auto& requiredComponent : component->getRequiredComponents()) {
            if (!hasComponent(requiredComponent)) {
                throw std::runtime_error("Entity missing required component");
                return false;
            }
        }
    }
    return true;
}

void Entity::init() {
    componentCheck();
    for (auto& component : components) {
        component->init();
    }
}