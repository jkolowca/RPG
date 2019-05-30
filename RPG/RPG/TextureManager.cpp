#include "TextureManager.h"

sf::Texture* TextureManager::GetResource(std::string _name) {
	if (!textures[_name]) {
		textures[_name] = new sf::Texture;
		textures[_name]->loadFromFile(_name);
		count[_name] = 0;
	}
	count[_name]++;
	return textures[_name];
}

void TextureManager::FreeResource(std::string _name) {
	count[_name]--;
	if (count[_name] == 0) {
		delete textures[_name];
		textures.erase(_name);
		count.erase(_name);
	}
}