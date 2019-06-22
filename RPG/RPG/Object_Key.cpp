#include "Object_Key.h"
#include "ObjectManager.h"

Key::Key(Shared *_shared, unsigned int _ID) : Object(_shared, "dep\\im\\key.png", { TileSize,TileSize }, _ID) {}

void Key::Interact() {
	OM->RemoveObj(ID);
}

void Key::SetObjectManager(ObjectManager* _om) {
	OM = _om;
}