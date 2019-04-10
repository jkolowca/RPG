#include "Screen_Intro.h"
#include "Shared.h"
#include "ScreenManager.h"

Screen_Intro::Screen_Intro(ScreenManager* _manager) : Screen(_manager), sprite("dep\\im\\i.png") {}
Screen_Intro::~Screen_Intro() {}

void Screen_Intro::Activate() {
	Position();
	manager->GetShared()->eventManager->AddCallback("select", &Screen_Intro::Interact, this);
	manager->GetShared()->eventManager->AddCallback("interact", &Screen_Intro::Interact, this);
}
void Screen_Intro::Deactivate() {
	manager->GetShared()->eventManager->RemoveCallback("select");
	manager->GetShared()->eventManager->RemoveCallback("interact");
}

void Screen_Intro::Update(const sf::Time& l_time) {}

void Screen_Intro::Draw() {
	sprite.Draw(manager->GetShared()->renderWindow);
	text.setString("165");
	manager->GetShared()->renderWindow->draw(text);
}

void Screen_Intro::Position() {
	sf::Vector2u windowSize = manager->GetShared()->renderWindow->getSize();
	sprite.SetPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f - 30));
	text.setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f - 30));
}

void Screen_Intro::Interact(sf::Event::KeyEvent) {
	manager->SwitchTo(MainMenu);
}