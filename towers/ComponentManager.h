#pragma once
#include "Object.h"
#include <array>
#include <map>

struct ComponentInstance {
    unsigned int index;
};

template <typename ComponentType>
struct ComponentData {
    unsigned int size = 1;
    std::array<ComponentType, 1024> data;
};

template <typename ComponentType>
class ComponentManager {
public:
    using LookupType = ComponentType;

    ComponentManager() {
        componentData.data = static_cast<std::array<ComponentType, 1024> *>(malloc(sizeof(ComponentType) * 1024));
    }

    // Add component to object
    ComponentInstance add(Object object, ComponentType& component) {
        ComponentInstance newInstance = { componentData.size };
        componentData.data.at(newInstance) = component;
        objectMap.add(object, newInstance);
        componentData.size++;
        return newInstance;
    }

    // Destroy the component related to object
    void destroyComponent(Object object) {
        ComponentInstance instance = objectMap.getInstance(object);

        // Move last component to the deleted position to maintain data coherence
        ComponentInstance lastComponent = componentData.size - 1;
        componentData.data.at(instance) = componentData.data.at(lastComponent);
        Object lastObject = objectMap.getObject(lastComponent);

        // Update our map
        objectMap.remove(object);
        objectMap.update(lastObject, instance);

        componentData.size--;
    }
    
    //Look up the component related to an entity
    LookupType* lookup(Object object) {
        ComponentInstance instance = objectMap.getInstance(object);
        return &componentData.data->at(instance);
    }

private:
    ComponentData<ComponentType> componentData;
    std::map<Object, ComponentInstance> objectMap;
};
