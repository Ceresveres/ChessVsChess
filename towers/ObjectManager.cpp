#include "ObjectManager.h"

Object ObjectManager::createObject() {
	lastObject++;
	return { lastObject };
}
