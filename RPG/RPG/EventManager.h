#pragma once
#include <string>
#include <unordered_map>
#include <SFML\Window\Event.hpp>

class EventManager {
public:
	EventManager();
	~EventManager();

	void AddCallback(std::string, void(*f)(sf::Event::KeyEvent));
	void RemoveCallbacks();
	void ImportHandles();

	void ProcessEvent(sf::Event);
	void Update();
private:
	std::unordered_map<std::string, void(*)(sf::Event::KeyEvent)> callbacks;
	std::unordered_map < int, std::string > handles;
	std::unordered_map < std::string, sf::Event::KeyEvent> events;
};