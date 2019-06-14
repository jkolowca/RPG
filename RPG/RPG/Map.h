#pragma once
#include "Shared.h"
#include <memory>

class Tile {
	Shared* shared;
	sf::Sprite sprite;
	sf::RenderWindow* window;
public:
	Tile(sf::Vector2i location, Shared* _shared);
	~Tile();
	void Draw();
	void Position(sf::Vector2f _position);
};

struct TileInfo {
	std::shared_ptr<Tile> tile;
	bool solid=false;
};

class Array3d {
public:
	Array3d() {};
	~Array3d();
	void Create(int _layer, int _column, int _row);

	TileInfo& operator()(int K, int L, int M);
	unsigned int layer, column, row;
	TileInfo* arr;
};

class Map {
public:
	Map(Shared* _shared);
	~Map() {}

	void Load(int _level);
	bool Draw(int _layer);
	bool MakeMove(int, int);


	sf::Vector2f getPlayerPosition() {
		return playerposition;
	}

	sf::Vector2f getPlayerShift() {
		return playerShift;
	}
private:
	void calculateMapPosition();
	sf::Vector2f playerposition, playerShift;
	sf::Vector2i playercoordinates;
	sf::Vector2i mapSize;
	int layers;
	Array3d map;
	Shared* shared;
	sf::Vector2i firstDrawn, margin, numberDrawn;
	sf::Vector2f offset;
};
