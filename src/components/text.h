#pragma once

#include "component.h"
#include "transform.h"
#include <SFML/Graphics.hpp>
#include <memory>

class GC_Text : public Component {
    REGISTER_GC(GC_Text)
private:
    std::unique_ptr<sf::Text> text;
    GC_Transform* transform;
public:
    GC_Text(const std::string& assetName, const std::string& contents);

    void init() override;
    void update() override;
    void render(sf::RenderTarget* target) override;
};