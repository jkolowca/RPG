#include "Highlight.h"

Highlight::Highlight() {
	SetSize(sf::Vector2f(72, 72));
	SetColor(sf::Color(80, 85, 84, 100));
	selected = false;
}
Highlight::~Highlight() {}

void Highlight::Draw(sf::RenderWindow* _window) {
	if(selected)
	_window->draw(rect);
}

bool Highlight::Clicked(sf::Vector2i _mousePos) {
	if (_mousePos.x >= rect.getPosition().x - rect.getSize().x / 2.0f &&
		_mousePos.x <= rect.getPosition().x + rect.getSize().x / 2.0f &&
		_mousePos.y >= rect.getPosition().y - rect.getSize().y / 2.0f &&
		_mousePos.y <= rect.getPosition().y + rect.getSize().y / 2.0f)
		return true;
	else
		return false;
}

void Highlight::SetColor(sf::Color _color) {
	rect.setFillColor(_color);
}

void Highlight::SetSize(sf::Vector2f _size) {
	rect.setSize(_size);
	rect.setOrigin(sf::Vector2f(_size.x / 2.0f, _size.y / 2.0f));
}

void Highlight::SetPosition(sf::Vector2f _position) {
	rect.setPosition(_position);
}

void Highlight::Select() {
	selected = true;
}

void Highlight::Deselect() {
	selected = false;
}

bool Highlight::IsSelected() {
	return selected;
}

sf::Vector2f Highlight::GetSize() {
	return rect.getSize();
}