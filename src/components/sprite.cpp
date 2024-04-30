#include "sprite.h"
#include "asset_manager.h"
#include "entity.h"
#include "transform.h"

SpriteComponent::SpriteComponent(const std::string& assetName) {
    sprite = std::make_unique<sf::Sprite>(*AssetManager::getTexture(assetName));
    require<TransformComponent>();
}

SpriteComponent::~SpriteComponent() {
}

void SpriteComponent::update() {
    auto transform = entity->getComponent<TransformComponent>();
    sprite->setPosition(transform->position);

    // Scale sprite so texture fits the entity
    sprite->setScale(transform->scale.x / sprite->getTexture()->getSize().x, transform->scale.y / sprite->getTexture()->getSize().y);
    // Center the sprite
    sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);

    sprite->setRotation(transform->rotation);
}

void SpriteComponent::render(sf::RenderTarget* target) {
    target->draw(*sprite);
}