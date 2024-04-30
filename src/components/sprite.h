#pragma once

#include "component.h"
#include <SFML/Graphics.hpp>

class SpriteComponent : public Component {
private:
    std::unique_ptr<sf::Sprite> sprite;

public:
    SpriteComponent(const std::string& assetName);
    ~SpriteComponent();
    void update() override;
    void render(sf::RenderTarget* target) override;
};
