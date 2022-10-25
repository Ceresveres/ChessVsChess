#pragma once
#include "EventBus.h"
#include "Object.h"

struct Event {

};

struct CollisionEvent : public Event {
    CollisionEvent(Object objectA, Object objectB) : objectA(objectA), objectB(objectB) {};
    Object objectA;
    Object objectB;
};

struct SpawnEvent : public Event {
    SpawnEvent(Object object) : object(object) {};
    Object object;
};