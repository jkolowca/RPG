#pragma once
#include "Object.h"

class ObjectFactory {
public:
	virtual Object* create(Shared* _shared, int _id) const = 0;
};