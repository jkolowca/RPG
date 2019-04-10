#include "Screen_MainMenu.h"
#include "ScreenManager.h"
#include "Application.h"

Screen_MainMenu::Screen_MainMenu(ScreenManager* _manager): Screen(_manager) {}
Screen_MainMenu::~Screen_MainMenu() {
	title.SetSize(25);
	title.SetText("MAIN MENU");


	std::string str[3];
	str[0] = "PLAY";
	str[1] = "LOAD GAME";
	str[2] = "EXIT";

	for (int i = 0; i < 3; ++i) {
		buttons[i].SetLabel(str[i]);
	}
}

void Screen_MainMenu::Activate() {
	Position();
	buttons[selected].Deselect();
	buttons[0].Select();
	selected = 0;
	manager->GetShared()->eventManager->AddCallback("select", &Screen_MainMenu::select, this);
	manager->GetShared()->eventManager->AddCallback("up", &Screen_MainMenu::up, this);
	manager->GetShared()->eventManager->AddCallback("down", &Screen_MainMenu::down, this);
	manager->GetShared()->eventManager->AddCallback("escape", &Screen_MainMenu::escape, this);
}
void Screen_MainMenu::Deactivate() {
	manager->GetShared()->eventManager->RemoveCallback("select");
	manager->GetShared()->eventManager->RemoveCallback("up");
	manager->GetShared()->eventManager->RemoveCallback("down");
	manager->GetShared()->eventManager->RemoveCallback("escape");
}

void Screen_MainMenu::Update(const sf::Time& l_time) {}
void Screen_MainMenu::Draw() {
	title.Draw(manager->GetShared()->window->GetRenderWindow());
	//for (int i = 0; i < 3; ++i) {
	//	buttons[i].Draw(manager->GetShared()->renderWindow);
	//}
}
void Screen_MainMenu::Position() {
	sf::Vector2u windowSize = manager->GetShared()->renderWindow->getSize();
	sf::Vector2f buttonPos = sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f - 0.5f*(buttons[0].GetSize().y + 10));

	title.SetPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 4.0f + 25));

	for (int i = 0; i < 3; ++i) {
		sf::Vector2f buttonPosition(buttonPos.x, buttonPos.y + (i * (buttons[0].GetSize().y + 10)) + 25);
		buttons[i].SetPosition(buttonPosition);
	}
}

void Screen_MainMenu::select(sf::Event::KeyEvent) {
	if (selected == 0) {
		manager->SwitchTo(Intro);
	}
	else if (selected == 1) {
		manager->SwitchTo(Intro);
	}
	else if (selected == 2) {
		manager->GetShared()->window->Close();
	}
}
void Screen_MainMenu::up(sf::Event::KeyEvent) {
	if (selected < 2) {
		buttons[selected++].Deselect();
		buttons[selected].Select();
	}
}
void Screen_MainMenu::down(sf::Event::KeyEvent) {
	if (selected > 0) {
		buttons[selected--].Deselect();
		buttons[selected].Select();
	}
}
void Screen_MainMenu::escape(sf::Event::KeyEvent) {
	manager->GetShared()->window->Close();
}
