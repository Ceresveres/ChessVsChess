#pragma once
#include <array>
#include <map>
#include "Object.h"

const int MAX_NUMBER_OF_COMPONENTS = 1024;
using ComponentInstance = unsigned int;

struct ObjectMap {
    Object getObject(ComponentInstance instance) { return instanceToObject.at(instance); }

    ComponentInstance getInstance(Object object) { return objectToInstance.at(object); }

    void add(Object object, ComponentInstance instance) {
        objectToInstance.insert({ object, instance });
        instanceToObject.at(instance) = object;
    }

    void update(Object object, ComponentInstance instance) {
        objectToInstance.at(object) = instance;
        instanceToObject.at(instance) = object;
    }

    void remove(Object object) { objectToInstance.erase(object); }

    std::map<Object, ComponentInstance> objectToInstance;
    std::array<Object, 1024> instanceToObject;
};
