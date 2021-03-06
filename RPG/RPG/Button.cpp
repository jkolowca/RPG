#include "Button.h"

Button::Button() {
	SetSize(sf::Vector2f(300.0f, 40.0f));
	SetLabel("");
	SetFont("dep\\norwester.otf", 15);
	SetColor(sf::Color(80, 85, 84));
	selected = false;
}
Button::~Button() {}

void Button::Draw(sf::RenderWindow* _window) {
	_window->draw(rect);
	label.Draw(_window);
}

void Button::SetLabel(const std::string& _label) {
	label.SetText(_label);
}

void Button::SetFont(const std::string& _font, unsigned int _size) {
	label.SetFont(_font);
	label.SetSize(_size);
}

void Button::SetColor(sf::Color _color) {
	rect.setFillColor(_color);
}

void Button::SetSize(sf::Vector2f _size) {
	rect.setSize(_size);
	rect.setOrigin(sf::Vector2f(_size.x / 2.0f, _size.y / 2.0f));
}

void Button::SetPosition(sf::Vector2f _position) {
	rect.setPosition(_position);
	label.SetPosition(_position);
}

void Button::Select() {
	selected = true;
	SetColor(sf::Color(110, 110, 110));
}

void Button::Deselect() {
	selected = false;
	SetColor(sf::Color(80, 80, 80));
}

bool Button::IsSelected() {
	return selected;
}

sf::Vector2f Button::GetSize() {
	return rect.getSize();
}

std::string Button::GetLabel() {
	return label.GetText();
}