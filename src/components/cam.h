#pragma once

#include "component.h"
#include "types.h"
#include "transform.h"
#include <SFML/Graphics.hpp>

class CamComponent : public Component {
private:
    TransformComponent* transform;
    sf::View* view;
public:
    f32 zoom;

    CamComponent();

    void init() override;
    void update() override;
};