#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <SFML\Window\Event.hpp>


class EventManager {
public:
	EventManager();
	~EventManager();

	template<class T>
	void AddCallback(std::string _name, void(T::*_function)(sf::Event::KeyEvent), T* _instance) {
		callbacks[_name] = std::bind(_function, _instance, std::placeholders::_1);
	}
	void RemoveCallback(std::string);
	void RemoveAllCallbacks();
	void ImportHandles();

	void ProcessEvent(sf::Event);
	void Update();
private:
	std::unordered_map <std::string, std::function<void(sf::Event::KeyEvent)>> callbacks;
	std::unordered_map < int, std::string > handles;
	std::unordered_map < std::string, sf::Event::KeyEvent> events;
};