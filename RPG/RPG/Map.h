#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include "Shared.h"

#define MAPSIZEX 100
#define MAPSIZEY 100
class Tile {
	sf::Sprite sprite;

};
struct TileInfo {
	std::shared_ptr<Tile> tile;
	bool solid;
};
class Map {
public:
	Map(Shared*);
	~Map();
	void Load(int);
	void Draw(sf::RenderWindow);
	void Position(sf::Vector2i);
private:
	sf::Vector2i begining;
	TileInfo map[MAPSIZEX][MAPSIZEY];

};