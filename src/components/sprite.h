#pragma once

#include "component.h"
#include <SFML/Graphics.hpp>

class SpriteComponent : public Component {
private:
    const char* path;
    sf::RenderTarget* target;
    sf::Sprite* sprite;

public:
    SpriteComponent(const std::string& assetName, sf::RenderTarget* target);
    ~SpriteComponent();
    void update() override;
    void render() override;
};
