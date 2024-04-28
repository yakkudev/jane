#pragma once
#include "entity.h"
#include <SFML/Graphics.hpp>

class Box : public Entity {
public:
    Box(sf::RenderTarget* target);
    ~Box();

    void update() override;
    void render() override;
};