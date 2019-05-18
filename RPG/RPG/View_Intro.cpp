#include "View_Intro.h"
#include "Shared.h"
#include "ViewManager.h"

View_Intro::View_Intro(ViewManager* _manager) : View(_manager), sprite("dep\\im\\i.png") {}
View_Intro::~View_Intro() {}

void View_Intro::Activate() {
	Position();
	manager->GetShared()->eventManager->AddCallback("select", &View_Intro::Interact, this);
	manager->GetShared()->eventManager->AddCallback("interact", &View_Intro::Interact, this);
	manager->GetShared()->eventManager->AddCallback("escape", &View_Intro::Escape, this);
}
void View_Intro::Deactivate() {
	manager->GetShared()->eventManager->RemoveCallback("select");
	manager->GetShared()->eventManager->RemoveCallback("interact");
	manager->GetShared()->eventManager->RemoveCallback("escape");
}

void View_Intro::Update(const sf::Time& l_time) {}

void View_Intro::Draw() {
	sprite.Draw(manager->GetShared()->renderWindow);
}

void View_Intro::Position() {
	sf::Vector2u windowSize = manager->GetShared()->renderWindow->getSize();
	sprite.SetPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f - 30));
}

void View_Intro::Interact(sf::Event::KeyEvent) {
	manager->SwitchTo(MainMenu);
}
void View_Intro::Escape(sf::Event::KeyEvent) {
	manager->GetShared()->window->Close();
}