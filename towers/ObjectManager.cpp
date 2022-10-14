#include "ObjectManager.h"

Object ObjectManager::createObject() {
	lastObject++;
	return { lastObject };
}


void ObjectManager::destroyObject(Object object) {
	lastObject--;
}