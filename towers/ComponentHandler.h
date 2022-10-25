//#pragma once
//#include "ComponentManager.h"
//#include "Object.h"
//
//template <typename ComponentType>
//struct ComponentHandler {
//    using ExposedComponentType = typename ComponentManager<ComponentType>::LookupType;
//
//    Object owner;
//    ExposedComponentType* component;
//    ComponentManager<ComponentType>* manager;
//
//    ComponentHandler() {};
//    ComponentHandler(Object owner, ExposedComponentType* component, ComponentManager<ComponentType>* manager) {
//        this->owner = owner;
//        this->component = component;
//        this->manager = manager;
//    }
//
//    ExposedComponentType* operator->() const { return component; }
//
//    void destroy() { manager->destroyComponent(owner); }
//};