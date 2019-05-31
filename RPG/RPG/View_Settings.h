#pragma once

#include "View.h"
#include "Button.h"

class View_Settings : public View {
public:
	View_Settings(ViewManager*);
	~View_Settings();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();
	void Position();

	void Escape(sf::Event::KeyEvent);

	void Select(sf::Event::KeyEvent);
	void Up(sf::Event::KeyEvent);
	void Down(sf::Event::KeyEvent);
	void Right(sf::Event::KeyEvent);
	void Left(sf::Event::KeyEvent);
	void KeyPressed(sf::Event::KeyEvent);
private:
	void AddCallbacks();
	void LoadSettings();

	Text title;
	Text labels[8];
	Button buttons[12];
	std::string key_names[101];
	int selected;
	Button save;
};