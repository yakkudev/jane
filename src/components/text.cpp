#include "asset_manager.h"
#include "text.h"
#include "transform.h"
#include "entity.h"

GC_Text::GC_Text(const std::string& assetName, const std::string& contents) {
    text = std::make_unique<sf::Text>();
    text->setFont(*AssetManager::getFont(assetName));
    text->setString(contents);
    require<GC_Transform>();
}


void GC_Text::init() {
    transform = entity->getComponent<GC_Transform>();
}

void GC_Text::update() {
    text->setPosition(transform->position);
    text->setRotation(transform->rotation);
    text->setCharacterSize(16);
}

void GC_Text::render(sf::RenderTarget* target) {
    target->draw(*text);
}

