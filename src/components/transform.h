#pragma once

#include "component.h"
#include "types.h"

class TransformComponent : public Component {
public:
    i32 x, y;

    TransformComponent(i32 x, i32 y);
};