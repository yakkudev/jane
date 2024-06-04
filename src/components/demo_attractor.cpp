#include "demo_attractor.h"
#include "game.h"
#include "transform.h"
#include "entity.h"
#include <cmath>

std::vector<GC_DemoAttractor*> GC_DemoAttractor::attractors;

GC_DemoAttractor::GC_DemoAttractor(f32 mass, f32 colorOffset, Vec2 velocity) {
    this->mass = mass;
    this->colorOffset = colorOffset;
    this->velocity = velocity;
    // this is not accurate, but makes planets visible
    this->radius = 2.0 * cbrt(mass) + 1.0f;

    shape.setFillColor(sf::Color::Green);

    require<GC_Transform>();
}

GC_DemoAttractor::GC_DemoAttractor(f32 mass, f32 radius, Vec2 velocity, bool isStatic) : GC_DemoAttractor(mass, radius, velocity) {
    this->isStatic = isStatic;
}

void GC_DemoAttractor::init() {
    this->transform = entity->getComponent<GC_Transform>();
    attractors.push_back(this);
}

void GC_DemoAttractor::clean() {
    attractors.erase(std::remove(attractors.begin(), attractors.end(), this), attractors.end());
}

void GC_DemoAttractor::simulate(GC_DemoAttractor* attractor) {
    if (isStatic) return;
    Vec2 dir = transform->position - attractor->transform->position;
    f32 distance = sqrt(dir.x * dir.x + dir.y * dir.y);

    if (distance == 0) return;

    Vec2 gravitationalForce = attract(attractor);

    if (distance < radius + attractor->radius) {
        if (std::find(collidedWith.begin(), collidedWith.end(), attractor) != collidedWith.end()) return;
        collidedWith.push_back(attractor);
        attractor->collidedWith.push_back(this);

        // Calc new velocities
        const f32 e = 0.6; // Coefficient of restitution
        Vec2 v1i = velocity;
        Vec2 v2i = attractor->velocity;
        f32 m1 = mass;
        f32 m2 = attractor->mass;

        if (attractor->isStatic) {
            v1i = velocity * 2;
            m1 = mass * 2;
        }

        // https://www.khanacademy.org/science/physics/linear-momentum/elastic-and-inelastic-collisions/a/what-are-elastic-and-inelastic-collisions
        Vec2 v1f = ((v1i * ((m1 - m2) * e)) + (v2i * 2 * m2 * e)) / (m1 + m2);
        Vec2 v2f = ((v2i * ((m2 - m1) * e) + (v1i * 2 * m1 * e))) / (m1 + m2);

        // apply gravity
        v1f += -gravitationalForce / m1;
        v2f += gravitationalForce / m2;

        // Update the velocities
        velocity = v1f;
        if (!attractor->isStatic) {
            attractor->velocity = v2f;
        }
    }
    else {
        // apply gravity
        velocity += -gravitationalForce / mass;
    }
    Vec2 nextPos1 = transform->position + velocity;
    Vec2 nextPos2 = attractor->transform->position + attractor->velocity;

    Vec2 nextDir = nextPos1 - nextPos2;
    f32 nextDistance = sqrt(nextDir.x * nextDir.x + nextDir.y * nextDir.y);

    // prevent overlap
    if (nextDistance < radius + attractor->radius) {
        Vec2 collisionNormal = normalized(dir);
        f32 overlap = radius + attractor->radius - distance;
        transform->position += collisionNormal * (overlap / 2);

        if (!attractor->isStatic) {
            attractor->transform->position -= collisionNormal * (overlap / 2);
        }
    }
}

Vec2 GC_DemoAttractor::attract(GC_DemoAttractor* attractor) {
    Vec2 direction = transform->position - attractor->transform->position;
    f32 dotProduct = dot(direction, direction);
    f32 distance = sqrt(dotProduct);
    f32 strength = (G * mass * attractor->mass) / dotProduct;

    if (dotProduct == 0) return Vec2(0, 0);
    return (direction / distance) * strength;
}

void GC_DemoAttractor::fixedUpdate() {
    // Very unoptimized
    for (auto& attractor : attractors) {
        attractor->collidedWith.clear();
    }

    // Collision
    for (auto& attractor : attractors) {
        if (attractor == this) continue;
        simulate(attractor);
    }
    if (isStatic) velocity = Vec2(0, 0);
    transform->position += velocity;
}

void GC_DemoAttractor::render(sf::RenderTarget* target) {

    // Draw line history
    const i32 maxPositions = 1000;
    sf::Vertex line[maxPositions];
    for (i32 i = 0; i < maxPositions; i++) {
        if (i >= positions.size()) break;
        line[i] = sf::Vertex(positions[i]);
        Color col = hsv(mass + colorOffset, 1.0, 1.0);
        line[i].color = Color(col.r, col.g, col.b, (i * 255 / positions.size()));
    }
    target->draw(line, positions.size(), sf::LineStrip, sf::RenderStates::Default);


    i32 samplingRate = 10;
    if ((velocity.x * velocity.x + velocity.y * velocity.y) > 100) samplingRate = 4;
    counter++;
    if (counter % samplingRate == 0) {
        positions.push_back(transform->position);
        if (positions.size() > maxPositions) {
            positions.erase(positions.begin());
        }
    }

    shape.setRadius(radius);
    shape.setPosition(transform->position);
    shape.setOrigin(radius, radius);
    shape.setFillColor(hsv(mass + colorOffset, 1.0, 1.0));
    target->draw(shape);
}