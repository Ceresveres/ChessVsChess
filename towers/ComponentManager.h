#pragma once
#include <array>
#include <map>
#include <string>
#include "Object.h"
#include "ObjectMap.h"


template<typename ComponentType>
struct ComponentData {
    unsigned int size = 1;
    std::array<ComponentType, 1024> *data;
};

class BaseComponentManager {
public:
    BaseComponentManager() = default;
    virtual ~BaseComponentManager() = default;
    BaseComponentManager(const BaseComponentManager&) = default;
    BaseComponentManager& operator=(const BaseComponentManager&) = default;
    BaseComponentManager(BaseComponentManager&&) = default;
    BaseComponentManager& operator=(BaseComponentManager&&) = default;
};

template <typename ComponentType>
class ComponentManager : public BaseComponentManager {
public:
    using LookupType = ComponentType;

    ComponentManager() {
        componentData.data = static_cast<std::array<ComponentType, 1024> *>(malloc(sizeof(ComponentType) * 1024));
    }
    ComponentInstance addComponent(Object object, ComponentType& component) {
        ComponentInstance newInstance = componentData.size;
        componentData.data->at(newInstance) = component;
        objectMap.add(object, newInstance);
        componentData.size++;
        return newInstance;
    }

    void destroyComponent(Object object) {
        ComponentInstance instance = objectMap.getInstance(object);

        ComponentInstance lastComponent = componentData.size - 1;
        componentData.data[instance] = componentData.data[lastComponent];
        Object lastObject = objectMap.getObject(lastComponent);

        objectMap.remove(object);
        objectMap.update(lastObject, instance);

        componentData.size--;
    }

    LookupType* lookup(Object object) {
        ComponentInstance instance = objectMap.getInstance(object);
        return &componentData.data->at(instance);
    }

private:
    ComponentData<ComponentType> componentData;
    ObjectMap objectMap;
};
