#pragma once

#include <vector>
#include "component.h"
#include "transform.h"
#include "types.h"

class GC_DemoManager : public Component {
    REGISTER_GC(GC_DemoManager)
private:
    Vec2 holdStart;
    Vec2 holdEnd;

    f32 spawnMass = 10;

public:

    void init() override;
    void update() override;
    void render(sf::RenderTarget* target) override;

};