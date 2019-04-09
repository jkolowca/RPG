#pragma once
#include "State.h"
#include "Shared.h"
class StateManager {
public:
	StateManager(Shared*);
	~StateManager();

	void SwitchTo(State*);

private:
	Shared* shared;
};