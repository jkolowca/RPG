#include "View_Story.h"
#include "ViewManager.h"
#include <regex>
#include <iostream>
#include <fstream>

View_Story::View_Story(ViewManager* _manager) : View(_manager) {
	sprite[1].setTexture(*manager->GetShared()->textureManager.GetResource("dep\\im\\fp.png"));
	sprite[1].setOrigin({ (float)sprite[1].getTextureRect().width / 2, (float)sprite[1].getTextureRect().height / 2 });
	Load(1);
	LoadConversation();
	text[activeSpeaker].SetText(texts.front());
	texts.erase(texts.begin());
	conversationLength--;
}
View_Story::~View_Story() {
	manager->GetShared()->textureManager.FreeResource(std::string("dep\\im\\f") + std::to_string(player) + ".png");
	manager->GetShared()->textureManager.FreeResource("dep\\im\\fp.png");
}

void View_Story::Activate() {
	Position();
	manager->GetShared()->eventManager->AddCallback("select", &View_Story::Interact, this);
	manager->GetShared()->eventManager->AddCallback("interact", &View_Story::Interact, this);
	manager->GetShared()->eventManager->AddCallback("escape", &View_Story::Escape, this);
}
void View_Story::Deactivate() {
	manager->GetShared()->eventManager->RemoveCallback("select");
	manager->GetShared()->eventManager->RemoveCallback("interact");
	manager->GetShared()->eventManager->RemoveCallback("escape");
}

void View_Story::Update() {}

void View_Story::Draw() {
		manager->GetShared()->renderWindow->draw(sprite[activeSpeaker]);
		text[activeSpeaker].Draw(manager->GetShared()->renderWindow);
}

void View_Story::Position() {
	sf::Vector2u windowSize = manager->GetShared()->renderWindow->getSize();
		sprite[0].setPosition({ windowSize.x / 4.0f, windowSize.y / 2.0f });
		text[0].SetPosition({ windowSize.x / 4.0f * 3, windowSize.y / 2.0f });
		sprite[1].setPosition({ windowSize.x / 4.0f *3, windowSize.y / 2.0f });
		text[1].SetPosition({ windowSize.x / 4.0f, windowSize.y / 2.0f });
}

void View_Story::LoadConversation() {
	player = conversations[conversation].player;
	manager->GetShared()->textureManager.FreeResource("dep\\im\\f" + std::to_string(player) + ".png");
	sprite[0].setTexture(*manager->GetShared()->textureManager.GetResource("dep\\im\\f" + std::to_string(player) +".png"));
	sprite[0].setOrigin({ (float)sprite[0].getTextureRect().width / 2, (float)sprite[0].getTextureRect().height / 2 });
	activeSpeaker = conversations[conversation].firstPlayer;
	conversationLength = conversations[conversation].length;
}

void View_Story::Interact(sf::Event::KeyEvent) {
	activeSpeaker = !activeSpeaker;
	if (!conversationLength) {
		conversation++;
		LoadConversation();
		manager->SwitchTo(Game);
		return;
	}
	text[activeSpeaker].SetText(texts.front());
	texts.erase(texts.begin());
	conversationLength--;
}

void View_Story::Escape(sf::Event::KeyEvent) {
	manager->GetShared()->window->Close();
}

void View_Story::Load(int _level) {
	std::string tmp = "dep\\story\\c" + std::to_string(_level) + ".txt";

	std::ifstream file;
	file.open(tmp);
	if (!file) {
		std::cout << "couldn't open script for level" << _level << std::endl;
		return;
	}

	std::regex c("(\\d*):(\\d*):(\\d*)");
	std::regex slash("\\\\");
	std::smatch m;

	getline(file, tmp, ';');
	while (std::regex_search(tmp, m, c)) {
		conversations.push_back({ stoi(m[1]), stoi(m[2]), (bool)stoi(m[3]) });
		getline(file, tmp, ';');
	}

	do { 
	std::regex_replace(tmp, slash, "\\");
	texts.push_back(tmp); 
	}
	while (getline(file, tmp, ';'));

	file.close();
}