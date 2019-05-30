#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <map>

class TextureManager {
public:
	TextureManager() {}
	~TextureManager() {}

	sf::Texture* GetResource(std::string _name);
	void FreeResource(std::string _name);

private:
	std::map<std::string, sf::Texture*> textures;
	std::map<std::string, int> count;
};