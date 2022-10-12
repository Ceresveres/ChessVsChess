#pragma once
#include "Object.h"

class ObjectManager {
public:
	Object createObject();

private:
	int lastObject = 0;
};
