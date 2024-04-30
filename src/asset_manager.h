#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetManager {
private:
    static std::map<std::string, sf::Texture*> textures;
    static std::map<std::string, sf::Font*> fonts;
public:
    static void init();
    static void clean();
    static void loadTexture(const std::string& name, const std::string& path);
    static void loadFont(const std::string& name, const std::string& path);
    static sf::Texture* getTexture(const std::string& name);
    static sf::Font* getFont(const std::string& name);
};