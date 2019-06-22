#pragma once
#include "Object_Factory.h"
#include "Object_Doors.h"

class DoorsFactory: public ObjectFactory {
public:
	virtual Doors* create(Shared* _shared, int _id)const {
		return new Doors(_shared, _id);
	}
};