#include "ObjectManager.h"
#include "ObjectMap.h"

Object ObjectManager::createObject() {
	lastObject++;
	return { lastObject };
}


void ObjectManager::destroyObject(Object object) {
	ObjectMap map;
	map.remove(object);
}