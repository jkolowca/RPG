#pragma once
#include "Screen.h"
#include <vector>
#include <map>
#include <functional>
#include "Shared.h"

enum ScreenType {
	Intro = 0,
	MainMenu,
	Load,
	Save,
	Game,
	Paused,
	GameOver,
};

class ScreenManager {
public:
	ScreenManager(Shared*);
	~ScreenManager();

	void Draw();

	void SwitchTo(ScreenType);
	Shared* GetShared();
private:
	void CreateState(ScreenType);
	void RemoveState(ScreenType);

	template<class T>
	void RegisterScreen(ScreenType _type) {
		screens[_type] = [this]() -> Screen*
		{
			return new T(this);
		};
	}

	std::vector<std::pair<ScreenType, Screen*>> screens_container;
	std::map<ScreenType, std::function<Screen*(void)>> screens;
	Shared* shared;
};