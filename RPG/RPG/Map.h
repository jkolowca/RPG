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

#define TileSize 72

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

class Array3d {
public:
	Array3d() {};
	~Array3d() {
		delete[]arr;
	};
	void create(int _layer, int _column, int _row) {
		delete[]arr;
		layer = _layer;
		column = _column;
		row = _row;
		arr = new TileInfo[layer*column*row];
	}

	TileInfo& operator()(int K, int L, int M) {
		return arr[(K*column + L)*row + M];
	}
	unsigned int layer, column, row;
	TileInfo* arr;
};

class Map {
public:
	Map(Shared* _shared) : shared(_shared) {
		player.setSize({ TileSize, TileSize });
		player.setFillColor(sf::Color::Red);
		player.setOrigin({ TileSize / 2, TileSize / 2 });
	}
	~Map() {}

	void Load(int _level);

	bool Draw(int _layer);
	bool MakeMove(int, int);
private:

	sf::Vector2i playerposition;
	sf::Vector2i mapSize;
	int layers;
	Array3d map;
	Shared* shared;
	sf::RectangleShape player;
};
