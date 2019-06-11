#pragma once
#include <SFML\Window\Event.hpp>

class ViewManager;

class View {
public:
	View(ViewManager*);
	virtual void Activate() = 0;
	virtual void Deactivate() = 0;
	virtual void Position() = 0;
	virtual void Draw() = 0;
protected:
	ViewManager * manager;
};