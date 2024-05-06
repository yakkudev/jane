#pragma once

#include "component.h"
#include "transform.h"
#include <SFML/Graphics.hpp>
#include <memory>

class GC_Sprite : public Component {
    REGISTER_GC(GC_Sprite)

private:
    std::unique_ptr<sf::Sprite> sprite;
    GC_Transform* transform;
public:
    GC_Sprite(const std::string& assetName);

    void init() override;
    void update() override;
    void render(sf::RenderTarget* target) override;

    sf::Sprite* getSprite();
};
