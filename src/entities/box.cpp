#include "box.h"

#include "components/transform.h"
#include "components/sprite.h"

Box::Box(sf::RenderTarget* target) {
    addComponent(new TransformComponent(0, 0));
    addComponent(new SpriteComponent("sheldon", target));
    addComponent(new SpriteComponent("goku", target));
}

void Box::update() {
    for (Component* component : components) {
        component->update();
    }
}

void Box::render() {
    for (Component* component : components) {
        component->render();
    }
}