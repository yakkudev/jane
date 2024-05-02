#include "component.h"
#include "entity.h"

void Component::setEntity(Entity* entity) {
    if (this->entity != nullptr) {
        throw std::runtime_error("Component already has entity");
        return;
    }
    this->entity = entity;
}

const std::vector<u32>& Component::getRequiredComponents() {
    return requiredComponents;
}

void Component::init() {}
void Component::update() {}
void Component::render(sf::RenderTarget* target) {}