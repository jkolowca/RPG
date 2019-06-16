#include "View_Story.h"
#include "ViewManager.h"

View_Story::View_Story(ViewManager* _manager) : View(_manager) {
	sprite.setTexture(*manager->GetShared()->textureManager.GetResource("dep\\im\\i.png"));
	sprite.setOrigin({ (float)sprite.getTextureRect().width / 2, (float)sprite.getTextureRect().height / 2 });
}
View_Story::~View_Story() {
	manager->GetShared()->textureManager.FreeResource("dep\\im\\i.png");
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
	manager->GetShared()->renderWindow->draw(sprite);
}

void View_Story::Position() {
	sf::Vector2u windowSize = manager->GetShared()->renderWindow->getSize();
	sprite.setPosition({ windowSize.x / 2.0f, windowSize.y / 2.0f });
}

void View_Story::Interact(sf::Event::KeyEvent) {
	manager->SwitchTo(MainMenu);
}
void View_Story::Escape(sf::Event::KeyEvent) {
	manager->GetShared()->window->Close();
}