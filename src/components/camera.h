#pragma once

#include "component.h"
#include "types.h"
#include "transform.h"
#include <SFML/Graphics.hpp>

class GC_Camera : public Component {
    REGISTER_GC(GC_Camera)
private:
    GC_Transform* transform;
    sf::View* view;
public:
    f32 zoom;

    GC_Camera();

    void init() override;
    void update() override;
};