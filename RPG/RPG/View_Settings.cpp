#include "View_Settings.h"
#include "Shared.h"
#include "ViewManager.h"
#include <Windows.h>
#include <fstream>
#include <iostream>
#include <stdio.h>

View_Settings::View_Settings(ViewManager* _manager) : View(_manager), 
key_names{"A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z",
"0","1","2","3","4","5","6","7","8","9","Escape", "Left Crtl","Left Shift","Left Alt","System","Right Crtl","Right Shift","Right Alt","System","Menu",
"[","]",";",",",".","'","/","\\","~","=","-","Space","Enter","Backspace","Tab","PageUp","PageDown","End","Home","Insert","Delete","+","-","*","/","Left Arrow","Right Arrow","Up Arrow", "Down Arrow",
"NumPad 0", "NumPad 1", "NumPad 2", "NumPad 3", "NumPad 4", "NumPad 5","NumPad 6", "NumPad 7", "NumPad 8", "NumPad 9", 
"F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12","F13","F14","F15","Pause" } {
	for (unsigned int i = 0; i < 12; i++){
		buttons[i].SetSize({ buttons[i].GetSize().x / 3,buttons[i].GetSize().y });
	}

	title.SetText("Settings:");
	title.SetSize(40);
	save.SetLabel("Save");
}
View_Settings::~View_Settings() {}

void View_Settings::LoadSettings() {
	std::ifstream file;
	file.open("dep\\keys.txt");
	if (!file) {
		std::cout << "couldn't load settings!";
		return;
	}

	std::string _name;
	int keyCode;
	char t;
	int i = 0;

	while (file >> _name) {
		labels[i].SetText(_name + ":");
		file >> keyCode >> t;
		buttons[i].SetLabel(key_names[keyCode]);
		if (t == ',') {
			file >> keyCode >> t;
			buttons[i + 4].SetLabel(key_names[keyCode]);
		}
		i++;
	}
	file.close();
}

void::View_Settings::AddCallbacks() {
	manager->GetShared()->eventManager->AddCallback("select", &View_Settings::Select, this);
	manager->GetShared()->eventManager->AddCallback("escape", &View_Settings::Escape, this);
	manager->GetShared()->eventManager->AddCallback("up", &View_Settings::Up, this);
	manager->GetShared()->eventManager->AddCallback("down", &View_Settings::Down, this);
	manager->GetShared()->eventManager->AddCallback("right", &View_Settings::Right, this);
	manager->GetShared()->eventManager->AddCallback("left", &View_Settings::Left, this);
}

void View_Settings::Activate() {
	LoadSettings();
	Position();
	AddCallbacks();
	if (selected > -2) buttons[selected].Deselect();
	selected = 0;
	buttons[selected].Select();
}

void View_Settings::Deactivate() {
	manager->GetShared()->eventManager->RemoveCallback("select");
	manager->GetShared()->eventManager->RemoveCallback("escape");
	manager->GetShared()->eventManager->RemoveCallback("up");
	manager->GetShared()->eventManager->RemoveCallback("down");
	manager->GetShared()->eventManager->RemoveCallback("right");
	manager->GetShared()->eventManager->RemoveCallback("left");
}

void View_Settings::Update(const sf::Time& l_time) {}

void View_Settings::Draw() {
	sf::RenderWindow* window = manager->GetShared()->renderWindow;
	for (unsigned int i = 0; i < 4; i++) {
		buttons[i].Draw(window);
		buttons[i + 4].Draw(window);
		buttons[i + 8].Draw(window);
		labels[i].Draw(window);
		labels[i + 4].Draw(window);
	}
	title.Draw(window);
	save.Draw(window);
}

void View_Settings::Position() {
	sf::Vector2u windowSize = manager->GetShared()->renderWindow->getSize();
	sf::Vector2f buttonSize = buttons[0].GetSize();

	title.SetPosition({ (float)windowSize.x / 2, (float)windowSize.y / 9 });
	save.SetPosition({ (float)windowSize.x / 2, (float)8 * windowSize.y / 9 });

	for (unsigned int i = 0; i < 4; i++) {
		labels[i].SetPosition
		({ (float)3*windowSize.x / 9, 
			windowSize.y / 2+10 - 5*buttonSize.y + 4*i*buttonSize.y/3 });
		labels[7 - i].SetPosition
		({ (float)3*windowSize.x / 9, 
			windowSize.y / 2+10 + 5* buttonSize.y-4*i*buttonSize.y/3 });
		buttons[i].SetPosition
		({ 3*windowSize.x / 9 + 2*buttonSize.x, 
			windowSize.y / 2+10 - 5 * buttonSize.y + 4 * i*buttonSize.y / 3 });
		buttons[7-i].SetPosition
		({ 3*windowSize.x / 9 + 2*buttonSize.x, 
			windowSize.y / 2+10 + 5 * buttonSize.y - 4 * i*buttonSize.y / 3 });
		buttons[11 - i].SetPosition
		({ 3*windowSize.x / 9 + 3*buttonSize.x+buttonSize.x/2, 
			windowSize.y / 2+10 + 5 * buttonSize.y - 4 * i*buttonSize.y / 3 });
	}
}

void View_Settings::Escape(sf::Event::KeyEvent) {
	manager->SwitchTo(MainMenu);
}
void View_Settings::Select(sf::Event::KeyEvent) {
	if (selected != -1) {
		Deactivate();
		manager->GetShared()->eventManager->AddCallback("keyPressed", &View_Settings::KeyPressed, this);
	}
	else Save();
}

void View_Settings::Save() {
	for (unsigned int i = 0; i < 11; i++) {
		for (unsigned int j = i + 1; j < 12; j++) {
			if (buttons[i].GetLabel() == buttons[j].GetLabel()) {
				buttons[i].Select();
				buttons[j].Select();
				return;
			}
		}
	}
	std::ofstream file("dep\\keystemp.txt");
	std::string temp;
	int code;
	for (unsigned int i = 0; i < 8; i++) {
		temp = labels[i].GetText();
		temp.pop_back();
		file << temp << " ";
		temp = buttons[i].GetLabel();
		for (unsigned int j = 0; j < 101; j++) {
			if (key_names[j] == temp) {
				code = j;
				break;
			}
		}
		file << code;
		if (i > 3) {
			temp = buttons[i+4].GetLabel();
			for (unsigned int j = 0; j < 101; j++) {
				if (key_names[j] == temp) {
					code = j;
					break;
				}
			}
			file << ", " << code;
		}
		file << ";\n";
	}
	file.close();
	remove("dep\\keys.txt");
	rename("dep\\keystemp.txt", "dep\\keys.txt");
	manager->GetShared()->eventManager->ImportHandles();
}
void View_Settings::Up(sf::Event::KeyEvent) {
	if (selected>0 && selected!=8) {
		buttons[selected].Deselect();
		selected--;
		buttons[selected].Select();
	}
	else if (selected == -1) {
		save.Deselect();
		selected = 7;
		buttons[selected].Select();
	}
}
void View_Settings::Down(sf::Event::KeyEvent) {
	if (selected!=-1&&selected!=7&&selected!=11) {
		buttons[selected].Deselect();
		selected++;
		buttons[selected].Select();
	}
	else if (selected == 7 || selected == 11) {
		buttons[selected].Deselect();
		selected = -1;
		save.Select();
	}
}
void View_Settings::Right(sf::Event::KeyEvent) {
	if (3<selected&&selected < 8) {
		buttons[selected].Deselect();
		selected+=4;
		buttons[selected].Select();
	}
}
void View_Settings::Left(sf::Event::KeyEvent) {
	if (7<selected &&selected< 12) {
		buttons[selected].Deselect();
		selected -= 4;
		buttons[selected].Select();
	}
}

void View_Settings::KeyPressed(sf::Event::KeyEvent _key) {
	buttons[selected].SetLabel(key_names[_key.code]);
	manager->GetShared()->eventManager->RemoveCallback("keyPressed");
	AddCallbacks();
}