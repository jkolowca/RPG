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
	std::smatch m;

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

			map[position.x][position.y].tile = existingTiles[{tiletype.x, tiletype.y}];
			tmp = m.suffix().str();
			position.x++;
		}
		position.y++;
	}

}

void Map::Draw() {
	sf::Vector2u windowsize = shared->renderWindow->getSize();
	sf::Vector2i margin = { (int)(windowsize.x / 2 - (TileSize / 2)) / TileSize+1,(int)(windowsize.y / 2 - (TileSize / 2)) / TileSize+1 };

	sf::Vector2i firstDrawn = { 0,0 }, numberDrawn = { 2 * margin.x + 1, 2 * margin.y + 1 };
	sf::Vector2f offset = { (float)windowsize.x/2 - margin.x*TileSize, (float)windowsize.y/2 - margin.y*TileSize };
	
	if (XSize < windowsize.x / TileSize) {
		numberDrawn.x = XSize;
		offset.x = TileSize / 2 + windowsize.x / 2 - XSize*TileSize/2;
	}
	else if (playerposition.x < margin.x) {
		numberDrawn.x = windowsize.x/TileSize +1;
		offset.x = TileSize / 2;
	}
	else if (XSize - playerposition.x - 1 < margin.x) {
		numberDrawn.x = windowsize.x / TileSize + 1;
		firstDrawn.x = XSize - numberDrawn.x;
		offset.x = (float)windowsize.x - numberDrawn.x*TileSize+TileSize/2;
	}
	else {
		firstDrawn.x = playerposition.x - margin.x;
	}

	if (YSize < windowsize.y / TileSize) {
		numberDrawn.y = YSize;
		offset.y = TileSize / 2 + windowsize.y / 2 - YSize*TileSize/2;
	}
	else if (playerposition.y < margin.y) {
		numberDrawn.y = windowsize.y / TileSize + 1;
		offset.y = TileSize / 2;
	}
	else if (YSize - playerposition.y - 1 < margin.y) {
		numberDrawn.y = windowsize.y / TileSize + 1;
		firstDrawn.y = YSize - numberDrawn.y;
		offset.y = (float)windowsize.y - numberDrawn.y*TileSize+TileSize/2;
	}
	else {
		firstDrawn.y = playerposition.y - margin.y;
	}


	for (int x = 0; x < numberDrawn.x; x++) {
		for (int y = 0; y < numberDrawn.y; y++) {
			if (firstDrawn.x + x == playerposition.x&&firstDrawn.y + y == playerposition.y) {
				player.setPosition({ offset.x + x * 72, offset.y + y * 72 });
			}
			if (map[firstDrawn.x + x][firstDrawn.y + y].tile) {
				
				map[firstDrawn.x + x][firstDrawn.y + y].tile->Position({ offset.x + x * 72, offset.y + y * 72 });
				map[firstDrawn.x + x][firstDrawn.y + y].tile->Draw();
			}
		}
	}
	shared->renderWindow->draw(player);

};