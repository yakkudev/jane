#pragma once

#include "component.h"
#include "types.h"
#include <SFML/Graphics.hpp>

class TransformComponent : public Component {
public:
    Vec2 position;
    Vec2 scale;
    f32 rotation;

    TransformComponent() : TransformComponent(0.0f, 0.0f) {}
    TransformComponent(f32 x, f32 y);
    TransformComponent(f32 x, f32 y, f32 scaleX, f32 scaleY);
    TransformComponent(f32 x, f32 y, f32 scaleX, f32 scaleY, f32 rotation);
    TransformComponent(const TransformComponent& other);
};