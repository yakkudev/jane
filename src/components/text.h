#pragma once

#include "component.h"
#include <SFML/Graphics.hpp>
#include <memory>

class GC_Text : public Component {
private:
    std::unique_ptr<sf::Text> text;

public:
    GC_Text(const std::string& assetName, const std::string& contents);
    ~GC_Text();
    void update() override;
    void render(sf::RenderTarget* target) override;
};