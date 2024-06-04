#pragma once

// #include <SFML/Graphics.hpp>
#include <vector>
#include "component.h"
#include "transform.h"
#include "types.h"

class GC_DemoAttractor : public Component {
    REGISTER_GC(GC_DemoAttractor)
private:
    sf::CircleShape shape;
    GC_Transform* transform;

    std::vector<Vec2> positions;

    u32 counter = 0;
public:
    GC_DemoAttractor(f32 mass, f32 colorOffset, Vec2 velocity);
    GC_DemoAttractor(f32 mass, f32 colorOffset, Vec2 velocity, bool isStatic);

    bool isStatic = false;
    f32 colorOffset = 0;
    f32 mass;
    f32 radius;
    const f32 G = 6.674;
    Vec2 velocity;

    std::vector<GC_DemoAttractor*> collidedWith;

    void init() override;
    void fixedUpdate() override;
    void render(sf::RenderTarget* target) override;
    void clean() override;

    Vec2 attract(GC_DemoAttractor* attractor);
    void simulate(GC_DemoAttractor* attractor);

    static std::vector<GC_DemoAttractor*> attractors;

};