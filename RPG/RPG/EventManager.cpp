#include "EventManager.h"
#include <iostream>
#include <fstream>

EventManager::EventManager() {
	ImportHandles();
}
EventManager::~EventManager(){}

void EventManager::AddCallback(std::string _name, void(*_function)(sf::Event::KeyEvent)) {
	callbacks[_name] = _function;
}

void EventManager::RemoveCallbacks() {
	callbacks.clear();
}

void EventManager::ImportHandles() {
	std::ifstream file;
	file.open("keys.txt"); 
	if (!file) {
		std::cout << "couldn't load settings!";
		return;
	}

	std::string _name;
	int keyCode;
	char t;

	while (file >> _name) {
	et1:	file >> keyCode >> t;
		handles[keyCode] = _name;
		if (t == ',') goto et1;
	}
	file.close();
}

void EventManager::ProcessEvent(sf::Event _event) {
	int keyCode;
	if (_event.type == sf::Event::KeyPressed) {
		keyCode = _event.key.code;
	}
	events[handles[keyCode]] = _event.key;
}

void EventManager::Update() {
	for (auto const& it : events) {
		if (callbacks[it.first]) {
			callbacks[it.first](it.second);
		}
	}
}