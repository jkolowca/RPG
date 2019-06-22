#pragma once
#include "Object_Factory.h"
#include "Object_Key.h"

class KeyFactory : public ObjectFactory {
public:
	virtual Key* create(Shared* _shared, int _id)const {
		return new Key(_shared, _id);
	}
};