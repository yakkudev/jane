#include "demo_attractor.h"
#include "game.h"
#include "transform.h"
#include "entity.h"
#include <cmath>

std::vector<GC_DemoAttractor*> GC_DemoAttractor::attractors;

GC_DemoAttractor::GC_DemoAttractor(float mass, float radius, Vec2 velocity) {
    this->mass = mass;
    this->radius = radius;
    this->velocity = velocity;

    shape.setFillColor(sf::Color::Green);

    require<GC_Transform>();
}

GC_DemoAttractor::GC_DemoAttractor(float mass, float radius, Vec2 velocity, bool isStatic) : GC_DemoAttractor(mass, radius, velocity) {
    this->isStatic = isStatic;
}

void GC_DemoAttractor::init() {
    this->transform = entity->getComponent<GC_Transform>();
    attractors.push_back(this);
}

GC_DemoAttractor::~GC_DemoAttractor() {
    attractors.erase(std::remove(attractors.begin(), attractors.end(), this), attractors.end());
}

void GC_DemoAttractor::attract(GC_DemoAttractor* attractor) {
    Vec2 force = transform->position - attractor->transform->position;
    f32 distance = sqrt(force.x * force.x + force.y * force.y);
    f32 strength = (G * mass * attractor->mass) / (distance * distance);

    // Prevent collision
    if (distance < radius + attractor->radius) {
        // Set transform of both objects to be outside of the collision
        // Taking into acconut the mass of the objects
        transform->position += force / distance * (radius + attractor->radius - distance) * (attractor->mass / (mass + attractor->mass));
        attractor->transform->position -= force / distance * (radius + attractor->radius - distance) * (mass / (mass + attractor->mass));
    }
    else {
        force = (force / distance) * strength;
        velocity -= force / mass;
    }

}

void GC_DemoAttractor::fixedUpdate() {
    for (auto& attractor : attractors) {
        if (attractor == this) continue;
        attract(attractor);
    }
    if (isStatic) return;
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
        if (positions.size() > 100) {
            positions.erase(positions.begin());
        }
    }
}