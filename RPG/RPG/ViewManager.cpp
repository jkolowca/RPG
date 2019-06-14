#include "ViewManager.h"
#include "View_Intro.h"
#include "View_MainMenu.h"
#include "View_Settings.h"
#include "View_Game.h"

ViewManager::ViewManager(Shared* _shared) {
	shared = _shared;
	RegisterView<View_Intro>(Intro);
	RegisterView<View_MainMenu>(MainMenu);
	RegisterView<View_Settings>(Settings);
	RegisterView<View_Game>(Game);
	SwitchTo(Intro);
}

ViewManager::~ViewManager() {}

void ViewManager::SwitchTo(ViewType _type) {
	for (auto itr = views_container.begin(); itr != views_container.end(); ++itr)
	{
		if (itr->first == _type) {
			views_container.back().second->Deactivate();
			ViewType tmp_type = itr->first;
			View* tmp_screen = itr->second;
			views_container.erase(itr);
			views_container.emplace_back(tmp_type, tmp_screen);
			tmp_screen->Activate();
			return;
		}
	}

	// State with l_type wasn't found.
	if (!views_container.empty())  views_container.back().second->Deactivate(); 
	CreateState(_type);
	views_container.back().second->Activate();
}

void ViewManager::CreateState(ViewType _type) {
	auto newView = views.find(_type);
	if (newView == views.end()) return; 
	View* screen = newView->second();
	views_container.emplace_back(_type, screen);

}
void ViewManager::RemoveState(ViewType _type) {
	for (auto itr = views_container.begin(); itr != views_container.end(); ++itr)
	{
		if (itr->first == _type) {
			delete itr->second;
			views_container.erase(itr);
			return;
		}
	}
}

Shared* ViewManager::GetShared() {
	return shared;
}

void ViewManager::Draw() {
	views_container.back().second->Draw();
}

void ViewManager::Update() {
	views_container.back().second->Update();
}

void ViewManager::Position() {
	views_container.back().second->Position();
}