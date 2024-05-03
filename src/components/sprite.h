#pragma once

#include "component.h"
#include <SFML/Graphics.hpp>
#include <memory>

class GC_Sprite : public Component {
private:
    std::unique_ptr<sf::Sprite> sprite;

public:
    GC_Sprite(const std::string& assetName);
    ~GC_Sprite();

    void update() override;
    void render(sf::RenderTarget* target) override;

    sf::Sprite* getSprite();
};
