#pragma once
#include "Text.h"

/*przycisk, reaguje na klikniecie, moze byc podswietlony*/
class Highlight {
public:
	Highlight();
	~Highlight();

	void Draw(sf::RenderWindow*);

	void SetColor(sf::Color);
	void SetSize(sf::Vector2f);
	void SetPosition(sf::Vector2f);
	void Clicked(sf::Vector2f);
	void Switch();
	void SetSelection(bool _t) {
		selected = _t;
	}
	bool IsSelected();

	sf::Vector2f GetSize();
private:
	bool selected;

	sf::RectangleShape rect;
};