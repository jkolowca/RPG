#pragma once
#include <SFML\Window\Event.hpp>

class ScreenManager;

class Screen {
public:
	Screen(ScreenManager*);
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
	virtual void Position() = 0;
	virtual void Draw() = 0;

	virtual void Key_Esc();
	virtual void Key_P();
	virtual void Space();
	virtual void TextEntered(sf::Event::KeyEvent);		//wprowadzono tekst, przyjmuje kod wprowadzonego znaku
protected:
	ScreenManager * manager;
};