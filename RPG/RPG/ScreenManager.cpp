#include "ScreenManager.h"
#include "Screen_Intro.h"
#include "Screen_MainMenu.h"

ScreenManager::ScreenManager(Shared* _shared) {
	shared = _shared;
	RegisterScreen<Screen_Intro>(Intro);
	RegisterScreen<Screen_MainMenu>(MainMenu);
	SwitchTo(Intro);
}

ScreenManager::~ScreenManager() {}

void ScreenManager::SwitchTo(ScreenType _type) {
	for (auto itr = screens_container.begin(); itr != screens_container.end(); ++itr)
	{
		if (itr->first == _type) {
			screens_container.back().second->Deactivate();
			ScreenType tmp_type = itr->first;
			Screen* tmp_screen = itr->second;
			screens_container.erase(itr);
			screens_container.emplace_back(tmp_type, tmp_screen);
			tmp_screen->Activate();
			return;
		}
	}

	// State with l_type wasn't found.
	if (!screens_container.empty())  screens_container.back().second->Deactivate(); 
	CreateState(_type);
	screens_container.back().second->Activate();
}

void ScreenManager::CreateState(ScreenType _type) {
	auto newScreen = screens.find(_type);
	if (newScreen == screens.end()) return; 
	Screen* screen = newScreen->second();
	screens_container.emplace_back(_type, screen);

}
void ScreenManager::RemoveState(ScreenType _type) {
	for (auto itr = screens_container.begin(); itr != screens_container.end(); ++itr)
	{
		if (itr->first == _type) {
			delete itr->second;
			screens_container.erase(itr);
			return;
		}
	}
}

Shared* ScreenManager::GetShared() {
	return shared;
}

void ScreenManager::Draw() {
	screens_container.back().second->Draw();
}