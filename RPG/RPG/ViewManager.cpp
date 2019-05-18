#include "ViewManager.h"
#include "View_Intro.h"
#include "View_MainMenu.h"

ViewManager::ViewManager(Shared* _shared) {
	shared = _shared;
	RegisterView<View_Intro>(Intro);
	RegisterView<View_MainMenu>(MainMenu);
	SwitchTo(Intro);
}

ViewManager::~ViewManager() {}

void ViewManager::SwitchTo(ViewType _type) {
	for (auto itr = screens_container.begin(); itr != screens_container.end(); ++itr)
	{
		if (itr->first == _type) {
			screens_container.back().second->Deactivate();
			ViewType tmp_type = itr->first;
			View* tmp_screen = itr->second;
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

void ViewManager::CreateState(ViewType _type) {
	auto newView = screens.find(_type);
	if (newView == screens.end()) return; 
	View* screen = newView->second();
	screens_container.emplace_back(_type, screen);

}
void ViewManager::RemoveState(ViewType _type) {
	for (auto itr = screens_container.begin(); itr != screens_container.end(); ++itr)
	{
		if (itr->first == _type) {
			delete itr->second;
			screens_container.erase(itr);
			return;
		}
	}
}

Shared* ViewManager::GetShared() {
	return shared;
}

void ViewManager::Draw() {
	screens_container.back().second->Draw();
}