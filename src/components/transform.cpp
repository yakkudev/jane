#include "transform.h"

GC_Transform::GC_Transform(f32 x, f32 y) {
    this->position = { x, y };
    this->scale = { 128.0f, 128.0f };
    this->rotation = 0.0f;
}

GC_Transform::GC_Transform(f32 x, f32 y, f32 scaleX, f32 scaleY) {
    this->position = { x, y };
    this->scale = { scaleX, scaleY };
    this->rotation = 0.0f;
}

GC_Transform::GC_Transform(f32 x, f32 y, f32 scaleX, f32 scaleY, f32 rotation) {
    this->position = { x, y };
    this->scale = { scaleX, scaleY };
    this->rotation = rotation;
}