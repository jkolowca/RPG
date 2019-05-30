#pragma once
#include "View.h"
#include <vector>
#include <map>
#include <functional>
#include "Shared.h"

enum ViewType {
	Intro = 0,
	MainMenu,
	Load,
	Save,
	Game,
	Paused,
	GameOver,
};

class ViewManager {
public:
	ViewManager(Shared*);
	~ViewManager();

	void Draw();

	void SwitchTo(ViewType);
	Shared* GetShared();
private:
	void CreateState(ViewType);
	void RemoveState(ViewType);

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