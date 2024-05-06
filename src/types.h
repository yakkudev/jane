#pragma once

typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;
static_assert(sizeof(i8) == 1, "i8 is not 8 bits");
static_assert(sizeof(i16) == 2, "i16 is not 16 bits");
static_assert(sizeof(i32) == 4, "i32 is not 32 bits");
static_assert(sizeof(i64) == 8, "i64 is not 64 bits");

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
static_assert(sizeof(u8) == 1, "u8 is not 8 bits");
static_assert(sizeof(u16) == 2, "u16 is not 16 bits");
static_assert(sizeof(u32) == 4, "u32 is not 32 bits");
static_assert(sizeof(u64) == 8, "u64 is not 64 bits");

typedef float f32;
typedef double f64;
static_assert(sizeof(f32) == 4, "f32 is not 32 bits");
static_assert(sizeof(f64) == 8, "f64 is not 64 bits");

typedef unsigned long long usize;
static_assert(sizeof(usize) == sizeof(void*), "usize is not the same size as a pointer");


// ==== SFML ====
#include <SFML/Graphics.hpp>

typedef sf::Vector2f Vec2;
typedef sf::Vector2i Vec2i;
typedef sf::Vector2u Vec2u;
typedef sf::Color Color;
typedef sf::RenderWindow Window;
typedef sf::Keyboard::Key KeyCode;
typedef sf::Mouse::Button MouseButton;

// ==== ENGINE ====
#define REGISTER_GC(comp) private: inline static i32 COMPONENT_REGISTRATION = ComponentManager::registerComponent<comp>();