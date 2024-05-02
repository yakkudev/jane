#include "sprite.h"
#include "asset_manager.h"
#include "entity.h"
#include "transform.h"

GC_Sprite::GC_Sprite(const std::string& assetName) {
    sprite = std::make_unique<sf::Sprite>(*AssetManager::getTexture(assetName));
    require<GC_Transform>();
}

GC_Sprite::~GC_Sprite() {
}

void GC_Sprite::update() {
    auto transform = entity->getComponent<GC_Transform>();
    sprite->setPosition(transform->position);

    // Scale sprite so texture fits the entity
    sprite->setScale(transform->scale.x / sprite->getTexture()->getSize().x, transform->scale.y / sprite->getTexture()->getSize().y);
    // Center the sprite
    sprite->setOrigin(sprite->getLocalBounds().width / 2, sprite->getLocalBounds().height / 2);

    sprite->setRotation(transform->rotation);
}

void GC_Sprite::render(sf::RenderTarget* target) {
    target->draw(*sprite);
}