#pragma once
#include "System.h"
#include <iostream>
#include "Scene.h"
#include "ComponentHandler.h"
#include "Component.h"
#include "ComponentManager.h"

class GraphicSystem : public System {
public:
    GraphicSystem() {
        signature.addComponent<Layer>();
        std::cout << "Made";
    }
    std::map<int, std::vector<Object>> registeredLayers;
    virtual void registerObject(Object const& object) override;

    void update();
    void draw();
};