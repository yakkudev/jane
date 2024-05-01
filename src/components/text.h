#pragma once

#include "component.h"
#include <SFML/Graphics.hpp>
#include <memory>

class TextComponent : public Component {
private:
    std::unique_ptr<sf::Text> text;

public:
    TextComponent(const std::string& assetName, const std::string& contents);
    ~TextComponent();
    void update() override;
    void render(sf::RenderTarget* target) override;
};