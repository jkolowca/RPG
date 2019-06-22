#pragma once
#include "View_GameOver.h"
#include "ViewManager.h"

View_GameOver::View_GameOver(ViewManager* _manager) : View(_manager) {
	text.SetText("Game Over");
	text.SetSize(30);
}
View_GameOver::~View_GameOver() {
	manager->GetShared()->textureManager.FreeResource("dep\\im\\i.png");
}

void View_GameOver::Activate() {
	manager->RemoveState(Game);
	manager->RemoveState(Story);
	Position();
	manager->GetShared()->eventManager->AddCallback("select", &View_GameOver::Interact, this);
	manager->GetShared()->eventManager->AddCallback("interact", &View_GameOver::Interact, this);
	manager->GetShared()->eventManager->AddCallback("escape", &View_GameOver::Escape, this);
}
void View_GameOver::Deactivate() {
	manager->GetShared()->eventManager->RemoveCallback("select");
	manager->GetShared()->eventManager->RemoveCallback("interact");
	manager->GetShared()->eventManager->RemoveCallback("escape");
}

void View_GameOver::Update() {}

void View_GameOver::Draw() {
	text.Draw(manager->GetShared()->renderWindow);
}

void View_GameOver::Position() {
	sf::Vector2u windowSize = manager->GetShared()->renderWindow->getSize();
	text.SetPosition({ windowSize.x / 2.0f, windowSize.y / 2.0f });
}

void View_GameOver::Interact(sf::Event::KeyEvent) {
	manager->SwitchTo(MainMenu);
}
void View_GameOver::Escape(sf::Event::KeyEvent) {
	manager->GetShared()->window->Close();
}