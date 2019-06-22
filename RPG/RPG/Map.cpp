#include "Map.h"
#include <regex>
#include <iostream>
#include <cmath>
#include <fstream>

	Tile::Tile(sf::Vector2i location, Shared* _shared, int level) : window(_shared->renderWindow), shared(_shared) {
	sprite.setTexture(*shared->textureManager.GetResource("dep\\ts\\lev" + std::to_string(level) + ".png"));
	sprite.setTextureRect({ location.x*TileSize, location.y*TileSize, TileSize, TileSize });
	sprite.setOrigin(TileSize / 2, TileSize / 2);
}
Tile::~Tile() {
	shared->textureManager.FreeResource("dep\\ts\\lev0.png");
	std::cout << "tile destroyed" << std::endl;
}
void Tile::Draw() {
	window->draw(sprite);
}
void Tile::Position(sf::Vector2f _position) {
	sprite.setPosition(_position);
}


Array3d::~Array3d() {
	delete[]arr;
};
void Array3d::Create(int _layer, int _column, int _row) {
	delete[]arr;
	layer = _layer;
	column = _column;
	row = _row;
	arr = new TileInfo[layer*column*row];
}
TileInfo& Array3d::operator()(int L, int C, int R) {
	return arr[(L*column + C)*row + R];
}


Map::Map(Shared* _shared) : shared(_shared) {
	moveTime = sf::milliseconds(300);
}

void Map::Load(int _level) {
	std::string tmp = "dep\\map\\lev" + std::to_string(_level) + ".txt";

	std::ifstream file;
	file.open(tmp);
	if (!file) {
		std::cout << "couldn't open map for level" << _level << std::endl;
		return;
	}

	int layer = 0;
	sf::Vector2i tile = { 0,0 }, tiletype;
	std::regex r("(\\d*):(\\d*),(\\w{1})");
	std::regex pp("(\\d*):(\\d*)");
	std::regex size("(\\d*)x(\\d*)x(\\d*)");
	std::smatch m;

	getline(file, tmp);
	std::regex_search(tmp, m, size);
	layers = stoi(m[1]);
	mapSize = { stoi(m[2]), stoi(m[3]) };

	getline(file, tmp);
	std::regex_search(tmp, m, pp);
	playerCoordinates = { stoi(m[1]),stoi(m[2]) };

	map.Create(layers, mapSize.x, mapSize.y);


	std::map<std::pair<int, int>, std::shared_ptr<Tile>> existingTiles;
	while (getline(file, tmp)) {
		if (!std::regex_search(tmp, m, r)) {
			tile = { 0,0 };
			layer++;
			continue;
		}
		tile.x = 0;
		while (std::regex_search(tmp, m, r)) {
			tiletype.x = stoi(m[1]);
			tiletype.y = stoi(m[2]);

			if (!existingTiles[{tiletype.x, tiletype.y}]) {
				std::cout << "creating tile: " << tiletype.x << ":" << tiletype.y << std::endl;
				std::shared_ptr<Tile> ptr(new Tile(tiletype, shared, _level));
				existingTiles[{tiletype.x, tiletype.y}] = ptr;
			}

			map(layer, tile.x, tile.y).tile = existingTiles[{tiletype.x, tiletype.y}];
			if (m[3] == 'y')
				map(layer, tile.x, tile.y).solid = true;
			else map(layer, tile.x, tile.y).solid = false;
			tmp = m.suffix().str();
			tile.x++;
		}
		tile.y++;
	}
	file.close();

	calculateMapPosition();
	oldPosition = position = newPosition;
	playerShift = shift = { 0,0 };
	marg = {0,0};

}

bool Map::Draw(int _layer) {
	if (_layer + 1 > layers) return false;

	for (int x = 0; x < numberDrawn.x; x++) {
		for (int y = 0; y < numberDrawn.y; y++) {
			if (map(_layer, firstDrawn.x + x,firstDrawn.y + y).tile) {
				
				map(_layer, firstDrawn.x + x, firstDrawn.y + y).tile->Position
				({ position.x + x * TileSize, position.y + y * TileSize });
				map(_layer, firstDrawn.x + x, firstDrawn.y + y).tile->Draw();
			}
		}
	}

	return true;
};

bool Map::MakeMove(sf::Vector2i _move) {
	if (isSolid({playerCoordinates.x+_move.x, playerCoordinates.y+_move.y})) return false;
	playerCoordinates += _move;
	calculateMapPosition();
	oldPosition = position;
	shift = { -1 * _move.x*shift.x, -1*_move.y*shift.y };
	playerShift = { _move.x*playerShift.x, _move.y*playerShift.y };
	C_Moveable::Move(shift);
	return true;
}

void Map::calculateMapPosition() {
	sf::Vector2f windowsize = { (float)shared->renderWindow->getSize().x, (float)shared->renderWindow->getSize().y };
	sf::Vector2i oldFirstDrawn = firstDrawn;
	sf::Vector2i margin = { (int)ceil((windowsize.x / 2 - (TileSize / 2)) / TileSize),(int)ceil((windowsize.y / 2 - (TileSize / 2)) / TileSize) };

	firstDrawn = { 0,0 };
	if ((float)mapSize.x < windowsize.x / TileSize) {
		numberDrawn.x = mapSize.x;
		newPosition.x = TileSize / 2 + windowsize.x / 2 - mapSize.x*TileSize / 2;
	}
	else if (playerCoordinates.x < margin.x) {
		numberDrawn.x = (int)windowsize.x / TileSize + 1;
		newPosition.x = TileSize / 2;
	}
	else if (mapSize.x - playerCoordinates.x - 1 < margin.x) {
		numberDrawn.x = (int)windowsize.x / TileSize + 1;
		firstDrawn.x = mapSize.x - numberDrawn.x;
		newPosition.x = windowsize.x - numberDrawn.x*TileSize + TileSize / 2;
	}
	else {
		numberDrawn.x = 2 * margin.x + 1;
		firstDrawn.x = playerCoordinates.x - margin.x;
		newPosition.x = windowsize.x / 2 - margin.x*TileSize;
		if(firstDrawn.x != oldFirstDrawn.x){
			numberDrawn.x++;
			marg.x = 1;
			if (firstDrawn.x > oldFirstDrawn.x) {
				marg.x = -1;
				firstDrawn.x--;
				newPosition.x -= TileSize;
			}
		}
	}

	if ((float)mapSize.y < windowsize.y / TileSize) {
		numberDrawn.y = mapSize.y;
		newPosition.y = TileSize / 2 + windowsize.y / 2 - mapSize.y*TileSize / 2;
	}
	else if (playerCoordinates.y < margin.y) {
		numberDrawn.y = (int)windowsize.y / TileSize + 1;
		newPosition.y = TileSize / 2;
	}
	else if (mapSize.y - playerCoordinates.y - 1 < margin.y) {
		numberDrawn.y = (int)windowsize.y / TileSize + 1;
		firstDrawn.y = mapSize.y - numberDrawn.y;
		newPosition.y = windowsize.y - numberDrawn.y*TileSize + TileSize / 2;
	}
	else {
		numberDrawn.y = 2 * margin.y + 1;
		firstDrawn.y = playerCoordinates.y - margin.y;
		newPosition.y = windowsize.y / 2 - margin.y*TileSize;
		if (firstDrawn.y != oldFirstDrawn.y) {
			numberDrawn.y++;
			marg.y = 1;
			if (firstDrawn.y > oldFirstDrawn.y) {
				marg.y = -1;
				firstDrawn.y--;
				newPosition.y -= TileSize;
			}
		}
	}

	if (firstDrawn != oldFirstDrawn)
		position = { (firstDrawn.x - oldFirstDrawn.x)* TileSize + position.x, (firstDrawn.y - oldFirstDrawn.y)* TileSize + position.y }; 

	shift = { abs(newPosition.x - position.x), abs(newPosition.y - position.y) };

	playerShift = { (TileSize - shift.x),(TileSize - shift.y) };
}

void Map::Update() {
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

sf::Vector2f Map::getPlayerShift() {
	return playerShift;
}

bool Map::isSolid(sf::Vector2i _coord) {
	bool s = false;
	for (int i = 0; i < layers; i++) {
		if (map(i, _coord.x, _coord.y).solid)
			s = true;
	}
	return s;
}

sf::Sprite& Map::getSprite() { return map(0, firstDrawn.x, firstDrawn.y).tile->getSprite(); }

sf::Vector2f Map::getTilePosition(sf::Vector2i _coord) {
	return { (_coord.x - firstDrawn.x) * TileSize + position.x, (_coord.y - firstDrawn.y)*TileSize + position.y };
}

sf::Vector2i Map::getPlayerCoordinates() {
	return playerCoordinates;
}