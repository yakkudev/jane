#pragma once

#include "types.h"
#include "component_manager.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Entity;
class Component {
protected:
    std::vector<u32> requiredComponents;
    Entity* entity = nullptr;
public:
    void setEntity(Entity* entity) {
        if (this->entity != nullptr) {
            throw std::runtime_error("Component already has entity");
            return;
        }
        this->entity = entity;
    }

    template<typename... required> void require() {
        (requiredComponents.push_back(ComponentManager::getComponentID<required>()), ...);
    }

    virtual void update() {}
    virtual void render(sf::RenderTarget* target) {}
};