#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include <regex>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>
#include "Shared.h"

enum MapSize {
	XSize = 30,
	YSize = 20,
	TileSize = 72,
	Layers = 2
};

class Tile {
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RenderWindow* window;
public:
	Tile(sf::Vector2i location, sf::RenderWindow* _window);
	void Draw();
	void Position(sf::Vector2f _position);
	~Tile() {}
};
struct TileInfo {
	std::shared_ptr<Tile> tile;
	bool solid;
};


class Map {
public:
	Map(Shared* _shared) : shared(_shared) {
		playerposition = { 0,0 };
		player.setSize({ TileSize, TileSize });
		player.setFillColor(sf::Color::Red);
		player.setOrigin({ TileSize / 2, TileSize / 2 });
	}
	~Map() {}

	void Load(int _level);

	void Draw();
	sf::Vector2i playerposition;
private:
	TileInfo map[XSize][YSize];
	Shared* shared;
	sf::RectangleShape player;
};