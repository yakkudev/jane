#include "asset_manager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

AssetManager* AssetManager::instance = nullptr;

AssetManager::AssetManager() {
    if (instance) {
        std::cerr << "AssetManager instance already exists" << std::endl;
        return;
    }
    instance = this;

    loadTexture("goku", "assets/goku.png");
    loadTexture("sheldon", "assets/sheldon.png");
}

AssetManager::~AssetManager() {
    // TODO: i think this causes a memory leak
    textures.clear();
    fonts.clear();
}

void AssetManager::loadTexture(const std::string& name, const std::string& path) {
    auto texture = new sf::Texture{};
    if (!texture->loadFromFile(path)) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        delete texture;
        return;
    }
    textures[name] = texture;
}

void AssetManager::loadFont(const std::string& name, const std::string& path) {
    auto font = new sf::Font{};
    if (!font->loadFromFile(path)) {
        std::cerr << "Failed to load font: " << path << std::endl;
        delete font;
        return;
    }
    fonts[name] = font;
}

sf::Texture* AssetManager::getTexture(const std::string& name) {
    return textures[name];
}

sf::Font* AssetManager::getFont(const std::string& name) {
    return fonts[name];
}

