#pragma once
#include "EventBus.h"
#include "Object.h"

struct Event {

};

struct CollisionEvent : public Event {
    CollisionEvent(Object object) : object(object) {};
    Object object;
};