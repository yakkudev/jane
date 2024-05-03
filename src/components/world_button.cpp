#include <SFML/Graphics.hpp>
#include <iostream>
#include "interaction.h"
#include "sprite.h"
#include "world_button.h"
#include "entity.h"

GC_WorldButton::GC_WorldButton() {
    require<GC_Interaction, GC_Sprite>();
}

void GC_WorldButton::init() {
    interaction = entity->getComponent<GC_Interaction>();
    sprite = entity->getComponent<GC_Sprite>();

    interaction->registerListener(std::bind(&GC_WorldButton::onClick, this), GC_Interaction::Type::MOUSE_UP);

}

void GC_WorldButton::onClick() {
    sprite->getSprite()->setColor(sf::Color::Red);
    std::cout << "Button clicked!" << std::endl;
}