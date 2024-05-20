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

    // Draw line history
    sf::Vertex line[400];
    for (i32 i = 0; i < 400; i++) {
        if (i >= positions.size()) break;
        line[i] = sf::Vertex(positions[i]);
        Color col = hsv(mass, 255, 255);
        line[i].color = Color(col.r, col.g, col.b, (i * 255 / positions.size()));
    }
    target->draw(line, positions.size(), sf::LineStrip, sf::RenderStates::Default);


    int samplingRate = 1;
    if (velocity.x * velocity.x + velocity.y * velocity.y < 10) samplingRate = 1;
    counter++;
    if (counter % samplingRate == 0) {
        positions.push_back(transform->position);
        if (positions.size() > 400) {
            positions.erase(positions.begin());
        }
    }

    shape.setRadius(radius);
    shape.setPosition(transform->position);
    shape.setOrigin(radius, radius);
    shape.setFillColor(hsv(mass, 255, 255));
    target->draw(shape);
}