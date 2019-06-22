#pragma once
#include "Object.h"

class Key : public Object {
public:
	Key(Shared *_shared, unsigned int _ID);

	void Interact();

	void SetObjectManager(ObjectManager* _om);
private:
	ObjectManager* OM;
};