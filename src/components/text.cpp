#include "asset_manager.h"
#include "text.h"
#include "transform.h"
#include "entity.h"

TextComponent::TextComponent(const std::string& assetName, const std::string& contents) {
    text = std::make_unique<sf::Text>();
    text->setFont(*AssetManager::getFont(assetName));
    text->setString(contents);
    require<TransformComponent>();
}

TextComponent::~TextComponent() {
}

void TextComponent::update() {
    auto transform = entity->getComponent<TransformComponent>();
    text->setPosition(transform->position);
    text->setRotation(transform->rotation);
    text->setCharacterSize(16);
}

void TextComponent::render(sf::RenderTarget* target) {
    target->draw(*text);
}

