#include "Map.h"

Tile::Tile(sf::Vector2i location, sf::RenderWindow* _window) : window(_window) {
	texture.loadFromFile("dep\\ts\\lev0.png");
	sprite.setTexture(texture);
	sprite.setTextureRect({ location.x*TileSize, location.y*TileSize, TileSize, TileSize });
	sprite.setOrigin(TileSize / 2, TileSize / 2);
}
void Tile::Draw() {
	window->draw(sprite);
}
void Tile::Position(sf::Vector2f _position) {
	sprite.setPosition(_position);
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
	sf::Vector2i position = { 0,0 }, tiletype;
	std::regex r("(\\d*):(\\d*)");
	std::regex size("(\\d*)x(\\d*)x(\\d*)");
	std::smatch m;

	getline(file, tmp);
	std::regex_search(tmp, m, size);
	layers = stoi(m[1]);
	mapSize = {stoi(m[2]), stoi(m[3])};

	mmap.create(layers, mapSize.x, mapSize.y);
	

	std::map<std::pair<int, int>, std::shared_ptr<Tile>> existingTiles;
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

			mmap(layer,position.x,position.y).tile = existingTiles[{tiletype.x, tiletype.y}];
			tmp = m.suffix().str();
			position.x++;
		}
		position.y++;
	}

}

int Map::Draw(int _layer) {
	if (_layer + 1 > layers)return -1;
	sf::Vector2i windowsize = { (int)shared->renderWindow->getSize().x, (int)shared->renderWindow->getSize().y };
	sf::Vector2i margin = { (windowsize.x / 2 - (TileSize / 2)) / TileSize+1,(windowsize.y / 2 - (TileSize / 2)) / TileSize+1 };

	sf::Vector2i firstDrawn = { 0,0 }, numberDrawn = { 2 * margin.x + 1, 2 * margin.y + 1 };
	sf::Vector2i offset = { windowsize.x/2 - margin.x*TileSize, windowsize.y/2 - margin.y*TileSize };
	
	if (mapSize.x < windowsize.x / TileSize) {
		numberDrawn.x = mapSize.x;
		offset.x = TileSize / 2 + windowsize.x / 2 - mapSize.x*TileSize/2;
	}
	else if (playerposition.x < margin.x) {
		numberDrawn.x = windowsize.x/TileSize +1;
		offset.x = TileSize / 2;
	}
	else if (mapSize.x - playerposition.x - 1 < margin.x) {
		numberDrawn.x = windowsize.x / TileSize + 1;
		firstDrawn.x = mapSize.x - numberDrawn.x;
		offset.x = windowsize.x - numberDrawn.x*TileSize+TileSize/2;
	}
	else {
		firstDrawn.x = playerposition.x - margin.x;
	}

	if (mapSize.y < windowsize.y / TileSize) {
		numberDrawn.y = mapSize.y;
		offset.y = TileSize / 2 + windowsize.y / 2 - mapSize.y*TileSize/2;
	}
	else if (playerposition.y < margin.y) {
		numberDrawn.y = windowsize.y / TileSize + 1;
		offset.y = TileSize / 2;
	}
	else if (mapSize.y - playerposition.y - 1 < margin.y) {
		numberDrawn.y = windowsize.y / TileSize + 1;
		firstDrawn.y = mapSize.y - numberDrawn.y;
		offset.y = windowsize.y - numberDrawn.y*TileSize+TileSize/2;
	}
	else {
		firstDrawn.y = playerposition.y - margin.y;
	}


	for (int x = 0; x < numberDrawn.x; x++) {
		for (int y = 0; y < numberDrawn.y; y++) {
			if (firstDrawn.x + x == playerposition.x&&firstDrawn.y + y == playerposition.y) {
				player.setPosition({ (float)offset.x + x * 72, (float)offset.y + y * 72 });
			}
			if (mmap(_layer, firstDrawn.x + x,firstDrawn.y + y).tile) {
				
				mmap(_layer, firstDrawn.x + x, firstDrawn.y + y).tile->Position({ (float)offset.x + x * 72, (float)offset.y + y * 72 });
				mmap(_layer, firstDrawn.x + x, firstDrawn.y + y).tile->Draw();
			}
		}
	}
	if (_layer + 1 != layers) {
		shared->renderWindow->draw(player);
	}
	return 1;

};