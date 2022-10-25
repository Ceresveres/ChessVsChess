//#pragma once
//#include "componentHandler.h"
//#include "Object.h"
//#include "Scene.h"
//
//class Scene;
//struct ObjectHandler {
//    Object object;
//    Scene* scene;
//
//    void destroy() { scene->destroyObject(object); }
//
//    template <typename ComponentType>
//    void addComponent(ComponentType&& component) {
//        scene->addComponent<ComponentType>(object, std::forward<ComponentType>(component));
//    }
//
//    template <typename ComponentType>
//    void removeComponent() {
//        scene->removeComponent<ComponentType>(object);
//    }
//
//    template <typename ComponentType>
//    ComponentHandler<ComponentType> getComponent() {
//        ComponentHandler<ComponentType> handle;
//        scene->unpack(object, handle);
//        return handle;
//    }
//};