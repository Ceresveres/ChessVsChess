#pragma once
#include "System.h"
#include <iostream>
#include "Scene.h"
#include "ComponentHandler.h"
#include "Component.h"
#include "ComponentManager.h"

class Map : public System {
public:
    Map() {
        signature.addComponent<Grid>();
        cout << "Made";
    }

    void update();
    void draw();
};