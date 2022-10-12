#pragma once
#include <vector>
#include <bitset>
#include "ComponentMap.h"
#include "Component.h"
#include "ComponentHandler.h"
#include "Object.h"

class Scene;
class System {
public:
	virtual void update() {};
    virtual void draw() {};
    virtual void init() {};
    void registerScene(Scene* scene) {
        parent = scene;
    }
    void registerObject(Object const& object);
    void unRegisterObject(Object const& object);
    ComponentMap getSignature();
protected:
    std::vector<Object> registeredObjects;
    Scene* parent;
    ComponentMap signature;
};