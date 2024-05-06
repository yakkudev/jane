#pragma once

#include "component.h"
#include "component_manager.h"
#include "types.h"
#include <SFML/Graphics.hpp>



class GC_Transform : public Component {
    REGISTER_GC(GC_Transform)

public:
    Vec2 position;
    Vec2 scale;
    f32 rotation;

    GC_Transform() : GC_Transform(0.0f, 0.0f) {}
    GC_Transform(f32 x, f32 y);
    GC_Transform(f32 x, f32 y, f32 scaleX, f32 scaleY);
    GC_Transform(f32 x, f32 y, f32 scaleX, f32 scaleY, f32 rotation);
};
