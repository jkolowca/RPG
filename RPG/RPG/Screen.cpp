#include "Screen.h"

Screen::Screen(ScreenManager* _manager): manager(_manager) {}
void Screen::Key_Esc() {}
void Screen::Key_P() {}
void Screen::Space() {}
void Screen::TextEntered(sf::Event::KeyEvent) {}