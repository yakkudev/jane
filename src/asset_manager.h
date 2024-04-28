#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class AssetManager {
private:
    std::map<std::string, sf::Texture*> textures;
    std::map<std::string, sf::Font*> fonts;
public:
    AssetManager();
    ~AssetManager();
    void loadTexture(const std::string& name, const std::string& path);
    void loadFont(const std::string& name, const std::string& path);
    sf::Texture* getTexture(const std::string& name);
    sf::Font* getFont(const std::string& name);

    static AssetManager* instance;
};