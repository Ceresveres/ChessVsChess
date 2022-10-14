#pragma once
#include "System.h"
#include <iostream>
#include "Scene.h"
#include "ComponentHandler.h"
#include "Component.h"
#include "ComponentManager.h"
#include "EventBus.h"

class EventBus;
class Piece : public System {
public:
    Piece() {
        
        signature.addComponent<Position>();
        signature.addComponent<Size>();
        signature.addComponent<StaticSprite>();
        cout << "Made";
    }

    void onCollisionEvent(CollisionEvent* collision) {

    }
    void init();
    void update();
    void draw();
};