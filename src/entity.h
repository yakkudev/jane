#pragma once

#include <vector>
#include "component.h"

class Entity {
protected:
    std::vector<Component*> components;

public:
    ~Entity();
    void addComponent(Component* component);
    void removeComponent(Component* component);
    virtual void update();
    virtual void render();

};