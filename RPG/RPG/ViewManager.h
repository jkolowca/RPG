#pragma once
#include "View.h"
#include <deque>
#include <map>
#include <functional>
#include "Shared.h"

enum ViewType {
	Intro = 0,
	MainMenu,
	Settings,
	Game,
	Story,
	GameOver,
	Save,
	Load,
	Paused,
};

class ViewManager {
public:
	ViewManager(Shared*);
	~ViewManager();

	void Draw();
	void Update();
	void Position();

	void SwitchTo(ViewType);
	Shared* GetShared();
	void CreateState(ViewType);
	void RemoveState(ViewType);
private:

	template<class T>
	void RegisterView(ViewType _type) {
		views[_type] = [this]() -> View*
		{
			return new T(this);
		};
	}

	std::vector<std::pair<ViewType, View*>> views_container;
	std::map<ViewType, std::function<View*(void)>> views;
	Shared* shared;
};