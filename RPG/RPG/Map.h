#pragma once
#include "Shared.h"
#include "C_Moveable.h"
#include <memory>

class Tile {
	Shared* shared;
	sf::Sprite sprite;
	sf::RenderWindow* window;
public:
	Tile(sf::Vector2i location, Shared* _shared);
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

	void Update() {
		if (moving) {
			if (moveClock.getElapsedTime() < moveTime) {
				position = { oldPosition.x + speed.x*moveClock.getElapsedTime().asSeconds(), oldPosition.y + speed.y*moveClock.getElapsedTime().asSeconds() };
			}
			else {
				position = newPosition;
				speed = shift = { 0,0 };
				moving = false;
				if (marg.x) {
					numberDrawn.x--;
					if (marg.x < 0) {
						firstDrawn.x++;
						position.x += TileSize;
					}
				}
				else if (marg.y) {
					numberDrawn.y--;
					if (marg.y < 0) {
						firstDrawn.y++;
						position.y += TileSize;
					}
				}
				marg = { 0,0 };
			}
		}
	}

	sf::Vector2f getPlayerShift() {
		return playerShift;
	}

	sf::Sprite& getSprite() { return map(0, firstDrawn.x, firstDrawn.y).tile->getSprite(); }

	bool isSolid(sf::Vector2i _coord) {
		bool s = false;
		for (int i = 0; i < layers; i++) {
			if (map(i, _coord.x, _coord.y).solid) 
				s = true;
		}
		return s;
	}

	sf::Vector2f getTilePosition(sf::Vector2i _coord) {
		return { (_coord.x - firstDrawn.x) * TileSize + position.x, (_coord.y - firstDrawn.y)*TileSize + position.y };
		//return position;
	}
	sf::Vector2f getPlayerPosition() {
		return getTilePosition(playerCoordinates);
	}
private:
	void calculateMapPosition();
	sf::Vector2i firstDrawn, numberDrawn;
	sf::Vector2i playerCoordinates;
	sf::Vector2f playerShift;
	sf::Vector2i mapSize;
	sf::Vector2f oldPosition, newPosition;
	sf::Vector2i marg;
	int layers;
	Array3d map;
	Shared* shared;
};
