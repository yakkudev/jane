#include "demo_attractor.h"
#include "game.h"
#include "transform.h"
#include "entity.h"
#include <cmath>

std::vector<GC_DemoAttractor*> GC_DemoAttractor::attractors;

GC_DemoAttractor::GC_DemoAttractor() {
    mass = 2000.0f;
    radius = 25.0f;
    shape.setFillColor(sf::Color::Green);

    require<GC_Transform>();
}

void GC_DemoAttractor::init() {
    this->transform = entity->getComponent<GC_Transform>();
    attractors.push_back(this);
    if (attractors.size() == 2) {
        velocity = { 5.0f, -9.0f };
        mass = 10.0f;
        radius = 5.0f;
    }

    if (attractors.size() == 3) {
        velocity = { 0.0f, -9.0f };
        mass = 0.00001f;
        radius = 1.0f;
    }
}

GC_DemoAttractor::~GC_DemoAttractor() {
    attractors.erase(std::remove(attractors.begin(), attractors.end(), this), attractors.end());
}

void GC_DemoAttractor::attract(GC_DemoAttractor* attractor) {
    Vec2 force = transform->position - attractor->transform->position;
    f32 distance = sqrt(force.x * force.x + force.y * force.y);
    f32 strength = (G * mass * attractor->mass) / (distance * distance);
    force = (force / distance) * strength;

    if (distance < radius + attractor->radius) {
        force = { 0.0f, 0.0f };
    }

    attractor->velocity += force / attractor->mass;
}

void GC_DemoAttractor::fixedUpdate() {
    for (auto& attractor : attractors) {
        if (attractor == this) continue;
        attract(attractor);
    }
    transform->position += velocity;
}

void GC_DemoAttractor::render(sf::RenderTarget* target) {
    shape.setRadius(radius);
    shape.setPosition(transform->position);
    shape.setOrigin(radius, radius);
    target->draw(shape);

    // Draw line history
    for (auto& p : positions) {
        sf::CircleShape circle(2.0f);
        // Different fill color for each attractor
        if (attractors[0] == this) {
            circle.setFillColor(sf::Color::Red);
        }
        else if (attractors[1] == this) {
            circle.setFillColor(sf::Color::Green);
        }
        else if (attractors[2] == this) {
            circle.setFillColor(sf::Color::Blue);
        }
        circle.setPosition(p);
        target->draw(circle);
    }

    counter++;
    if (counter % 5 == 0) {
        positions.push_back(transform->position);
        if (positions.size() > 500) {
            positions.erase(positions.begin());
        }
    }
}