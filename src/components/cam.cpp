#include "cam.h"
#include "game.h"
#include "transform.h"
#include "entity.h"
#include "input_manager.h"

CamComponent::CamComponent() {
    zoom = 1.0f;
    view = Game::getView();

    require<TransformComponent>();
}

void CamComponent::init() {
    view->setCenter(0, 0);
    transform = entity->getComponent<TransformComponent>();
}

void CamComponent::update() {

    if (InputManager::getMouseButton(MouseButton::Left)) {
        transform->position.x -= InputManager::getMouseDelta().x / zoom;
        transform->position.y -= InputManager::getMouseDelta().y / zoom;
    }

    if (InputManager::getMouseWheel() > 0) {
        zoom += 0.1f * zoom;
        if (zoom > 10.0f) {
            zoom = 10.0f;
        }
        // Scroll into the mouse position
        Vec2 worldPos = InputManager::getMouseWorldPosition();
        transform->position += (worldPos - transform->position) * 0.1f;
    }
    else if (InputManager::getMouseWheel() < 0) {
        zoom -= 0.1f * zoom;
        if (zoom < 0.1f) {
            zoom = 0.1f;
        }
    }

    view->setCenter(transform->position);
    view->setSize(Game::getWindow()->getSize().x / zoom, Game::getWindow()->getSize().y / zoom);
    Game::getWindow()->setView(*view);
}