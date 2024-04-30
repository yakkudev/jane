#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "component.h"

class Entity {
protected:
    sf::RenderTarget* target;
    std::vector<Component*> components;

public:
    Entity(sf::RenderTarget* target);
    ~Entity();
    Entity* addComponent(Component* component);
    void removeComponent(Component* component);

    bool hasComponent(Component* component);

    template <typename T> bool hasComponent() {
        for (auto& component : components) {
            if (typeid(*component) == typeid(T)) {
                return true;
            }
        }
        return false;
    }

    template <typename T> T* getComponent() {
        for (auto& component : components) {
            if (typeid(*component) == typeid(T)) {
                return static_cast<T*>(component);
            }
        }
        return nullptr;
    }

    virtual void update();
    virtual void render();

};