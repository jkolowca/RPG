#pragma once
#include "Shared.h"
#include "C_Moveable.h"
#include <memory>

class Tile {
	Shared* shared;
	sf::Sprite sprite;
	sf::RenderWindow* window;
public:
	Tile(sf::Vector2i location, Shared* _shared, int level);
	~Tile();
	sf::Sprite& getSprite(){ return sprite; }
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

class Map : public C_Moveable {
public:
	Map(Shared* _shared);
	~Map() {}

	void Load(int _level);
	bool Draw(int _layer);
	bool MakeMove(int, int);

	void Update();
	sf::Vector2f getPlayerShift();

	sf::Sprite& getSprite();

	bool isSolid(sf::Vector2i _coord);

	sf::Vector2f getTilePosition(sf::Vector2i _coord);
	sf::Vector2i getPlayerCoordinates() {
		return playerCoordinates;
	}
	//sf::Vector2f getPlayerPosition();
	void calculateMapPosition();
private:
	sf::Vector2i firstDrawn, numberDrawn;
	sf::Vector2i playerCoordinates;
	sf::Vector2f playerShift;
	sf::Vector2f oldPosition, newPosition;
	sf::Vector2i marg;
	sf::Vector2i mapSize;
	int layers;
	Array3d map;
	Shared* shared;
};
