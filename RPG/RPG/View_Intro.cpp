#include "View_Intro.h"
#include "Shared.h"
#include "ViewManager.h"

View_Intro::View_Intro(ViewManager* _manager) : View(_manager) {
	sprite.setTexture(*manager->GetShared()->textureManager.GetResource("dep\\im\\i.png"));
	sprite.setOrigin({ (float)sprite.getTextureRect().width / 2, (float)sprite.getTextureRect().height / 2 });
}
View_Intro::~View_Intro() {
	manager->GetShared()->textureManager.FreeResource("dep\\im\\i.png");
}

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
	manager->GetShared()->renderWindow->draw(sprite);
}

void View_Intro::Position() {
	sf::Vector2u windowSize = manager->GetShared()->renderWindow->getSize();
	sprite.setPosition({ windowSize.x / 2.0f, windowSize.y / 2.0f - 30 });
}

void View_Intro::Interact(sf::Event::KeyEvent) {
	manager->SwitchTo(MainMenu);
}
void View_Intro::Escape(sf::Event::KeyEvent) {
	manager->GetShared()->window->Close();
}