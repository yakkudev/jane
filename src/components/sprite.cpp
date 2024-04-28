#include "asset_manager.h"
#include "sprite.h"

SpriteComponent::SpriteComponent(const std::string& assetName, sf::RenderTarget* target) {
    this->path = path;
    this->target = target;
    sprite = new sf::Sprite(*AssetManager::instance->getTexture(assetName));
}

SpriteComponent::~SpriteComponent() {
}

void SpriteComponent::update() {
}

void SpriteComponent::render() {
    target->draw(*sprite);
}