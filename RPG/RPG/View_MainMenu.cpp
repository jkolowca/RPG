#include "View_MainMenu.h"
#include "ViewManager.h"

View_MainMenu::View_MainMenu(ViewManager* _manager) : View(_manager) {
	title.SetSize(25);
	title.SetText("MAIN MENU");


	buttons[0].SetLabel("PLAY");
	buttons[1].SetLabel("SETTINGS");
	buttons[2].SetLabel("EXIT");
}
View_MainMenu::~View_MainMenu() {}

void View_MainMenu::Activate() {
	Position();
	buttons[selected].Deselect();
	buttons[0].Select();
	selected = 0;
	manager->GetShared()->eventManager->AddCallback("select", &View_MainMenu::select, this);
	manager->GetShared()->eventManager->AddCallback("up", &View_MainMenu::up, this);
	manager->GetShared()->eventManager->AddCallback("down", &View_MainMenu::down, this);
	manager->GetShared()->eventManager->AddCallback("escape", &View_MainMenu::escape, this);
}
void View_MainMenu::Deactivate() {
	manager->GetShared()->eventManager->RemoveCallback("select");
	manager->GetShared()->eventManager->RemoveCallback("up");
	manager->GetShared()->eventManager->RemoveCallback("down");
	manager->GetShared()->eventManager->RemoveCallback("escape");
	buttons[selected].Deselect();
}

void View_MainMenu::Update() {}
void View_MainMenu::Draw() {
	for (int i = 0; i < 3; ++i) {
		buttons[i].Draw(manager->GetShared()->renderWindow);
	}
	title.Draw(manager->GetShared()->renderWindow);
}
void View_MainMenu::Position() {
	sf::Vector2u windowSize = manager->GetShared()->renderWindow->getSize();
	sf::Vector2f buttonPos = sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f - 0.5f*(buttons[0].GetSize().y + 10));

	title.SetPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 4.0f + 25));

	for (int i = 0; i < 3; ++i) {
		sf::Vector2f buttonPosition(buttonPos.x, buttonPos.y + (i * (buttons[0].GetSize().y + 10)) + 25);
		buttons[i].SetPosition(buttonPosition);
	}
}

void View_MainMenu::select(sf::Event::KeyEvent) {
	if (selected == 0) {
		if (first) {
			manager->SwitchTo(Story);
			first = false;
		}
		else manager->SwitchTo(Game);
	}
	else if (selected == 1) {
		manager->SwitchTo(Settings);
	}
	else if (selected == 2) {
		//manager->GetShared()->window->Close();
	}
}
void View_MainMenu::up(sf::Event::KeyEvent) {
	if (selected > 0) {
		buttons[selected].Deselect();
		selected--;
		buttons[selected].Select();
	}
}
void View_MainMenu::down(sf::Event::KeyEvent) {
	if (selected < 2) {
		buttons[selected].Deselect();
		selected++;
		buttons[selected].Select();
	}
}
void View_MainMenu::escape(sf::Event::KeyEvent) {
	manager->GetShared()->window->Close();
}
