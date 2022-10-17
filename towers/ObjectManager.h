#pragma once
#include "Object.h"

class ObjectManager {
public:
	Object createObject();
	void destroyObject(Object object);

private:
	int lastObject = 1;
};
