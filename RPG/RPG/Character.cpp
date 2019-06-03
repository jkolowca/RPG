#include "Character.h"


Character::Character(EntityManager* l_entityMgr)
	:EntityBase(l_entityMgr)
{
	m_name = "Character";
}




Character::~Character()
{
}

void Character::Load(const std::string & l_path)
{
	std::ifstream file;
	file.open(l_path);
	if (!file.is_open()) {
		std::cout << "! Failed loading tile set file: "
			<< l_path << std::endl;
		return;
	}
	std::string line;
	while (std::getline(file,line)){
		if (line[0] == '|') { continue; }
		std::stringstream keystream(line);
		std::string type;
		keystream >> type;
		if (type == "Name") {
			keystream >> m_name;
		}
		else if (type == "Spritesheet") {
			std::string path;
			keystream >> path;
			m_spriteSheet.SetTexture(path);
		}
		else if (type == "BoundingBox") {
			sf::Vector2f boundingSize;
			keystream >> boundingSize.x >> boundingSize.y;
			SetSize(boundingSize.x, boundingSize.y);
		}
		else if (type == "Speed") {
			keystream >> m_velocity.x >>m_velocity.y;
		}
		else {
			std::cout << "! Unknown type in character file: "
				<< type << std::endl;
		}
	}
	file.close();


}

void Character::Update(float l_dT)
{
	EntityBase::Update(l_dT);
	m_spriteSheet.SetPosition(m_position);
}

void Character::Draw(sf::RenderWindow * l_wind)
{
	m_spriteSheet.Draw(l_wind);
}

