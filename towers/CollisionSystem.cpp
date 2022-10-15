#include "CollisionSystem.h"

void CollisionSystem::init() {
    eventBus = parent->getEventBus();
}

void CollisionSystem::update() {
    for (auto& objectA : registeredObjects) {
        for (auto& objectB : registeredObjects) {
            if (objectB.id == objectA.id) continue;
            ComponentHandler<BoundingBox> boundingBoxA;
            parent->unpack(objectA, boundingBoxA);
            ComponentHandler<BoundingBox> boundingBoxB;
            parent->unpack(objectB, boundingBoxB);
            if (hasBoundingBoxOverlap(boundingBoxA.component, boundingBoxB.component)) {
                std::cout << "test";
                eventBus->publish(new CollisionEvent(objectA, objectB));
            }
        }
    }
}

void CollisionSystem::draw() {
    
}

bool CollisionSystem::hasBoundingBoxOverlap(BoundingBox* a, BoundingBox* b)
{
    float d1x = b->grid.x - (a->grid.x + a->grid.w);
    float d1y = b->grid.y - (a->grid.y + a->grid.h);
    float d2x = a->grid.x - (b->grid.x + b->grid.w);
    float d2y = a->grid.y - (b->grid.y + b->grid.h);

    if (d1x > 0.0f || d1y > 0.0f)
        return false;

    if (d2x > 0.0f || d2y > 0.0f)
        return false;

    return true;
}