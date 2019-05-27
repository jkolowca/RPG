#pragma once
#include <SFML\Graphics.hpp>
#include <memory>
#include <regex>
#include <fstream>
#include <iostream>
#include <map>
#include "Shared.h"

enum MapSize {
	XSize = 100,
	YSize = 100,
	TileSize = 72,
	Layers = 2
};
class Tile {
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RenderWindow* window;
public:
	Tile(sf::Vector2i location, sf::RenderWindow* _window): window(_window) {
		texture.loadFromFile("dep\\ts\\lev0.png");
		sprite.setTexture(texture);
		sprite.setTextureRect({location.x*TileSize, location.y*TileSize, TileSize, TileSize});
		sprite.setOrigin(32, 32);
	}
	void Draw() {
		window->draw(sprite);
	}
	void Position(sf::Vector2f _position) {
		sprite.setPosition(_position);
	}
	~Tile() {}
};
struct TileInfo {
	std::shared_ptr<Tile> tile;
	bool solid;
};


class Map {
public:
	Map(Shared* _shared) : shared(_shared) {} 
	~Map() {}

	void Load(int _level) {
		std::string tmp = "dep\\map\\lev" + std::to_string(_level) + ".txt";
		
		std::ifstream file;
		file.open(tmp);
		if (!file) {
			std::cout << "couldn't open map for level" << _level << std::endl;
			return;
		}

		int layer = 0;
		sf::Vector2i position = { 0,0 }, tiletype;
		std::regex r("(\\d*):(\\d*)");
		std::smatch m;

		std::map<std::pair<int,int>, std::shared_ptr<Tile>> existingTiles;
		while (getline(file, tmp)) {
			if (!std::regex_search(tmp, m, r)) {
				position = { 0,0 };
				layer++;
				continue;
			}
			position.x = 0;
			while (std::regex_search(tmp, m, r)) {
				tiletype.x = stoi(m[1]);
				tiletype.y = stoi(m[2]);

				if (!existingTiles[{tiletype.x, tiletype.y}]) {
					std::cout << "creating tile: " << tiletype.x << ":" << tiletype.y << std::endl;
					std::shared_ptr<Tile> ptr(new Tile(tiletype, shared->renderWindow));
					existingTiles[{tiletype.x, tiletype.y}] = ptr;
				}

				map[layer][position.x][position.y].tile = existingTiles[{tiletype.x, tiletype.y}];
				tmp = m.suffix().str();
				position.x++;
			}
			position.y++;
		}

	}

	void Draw(int _layer) {
		for (int x = 0; x < XSize; x++) {
			for (int y = 0; y < YSize; y++) {
				if (map[_layer][x][y].tile) {
					map[_layer][x][y].tile->Position({ (float)36+x*72, (float)36 +y*72});
					map[_layer][x][y].tile->Draw();
				}
			}
	}
	};
	void Position(sf::Vector2i) {};
private:
	sf::Vector2i begining;
	TileInfo map[Layers][XSize][YSize];
	Shared* shared;
};