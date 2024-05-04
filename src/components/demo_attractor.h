#pragma once

// #include <SFML/Graphics.hpp>
#include <vector>
#include "component.h"
#include "transform.h"
#include "types.h"

class GC_DemoAttractor : public Component {
private:
    sf::CircleShape shape;
    GC_Transform* transform;

    std::vector<Vec2> positions;

    int counter = 0;
public:
    GC_DemoAttractor(float mass, float radius, Vec2 velocity);
    ~GC_DemoAttractor();

    float mass;
    float radius;
    const float G = 10;
    Vec2 velocity;

    void init() override;
    void fixedUpdate() override;
    void render(sf::RenderTarget* target) override;

    void attract(GC_DemoAttractor* attractor);

    static std::vector<GC_DemoAttractor*> attractors;

};