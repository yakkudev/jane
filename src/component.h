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

    template<typename... required> void require() {
        (requiredComponents.push_back(ComponentManager::getComponentID<required>()), ...);
    }
public:
    void setEntity(Entity* entity);
    const std::vector<u32>& getRequiredComponents();

    virtual void init();
    virtual void update();
    virtual void render(sf::RenderTarget* target);
};