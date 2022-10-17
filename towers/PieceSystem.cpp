#include "PieceSystem.h"

void Piece::init() {
    eventBus = parent->getEventBus();
    eventBus->subscribe(this, &Piece::onCollisionEvent);
}

void Piece::update() {
    for (auto& object : registeredObjects) {
        ComponentHandler<Motion> motion;
        ComponentHandler<BoundingBox> boundingBox;

        parent->unpack(object, motion, boundingBox);

        *boundingBox.component += *motion.component;
    }
}

void Piece::draw() {
    //int tmpColor[4] = { 16, 143, 50, 255 };
    //for (auto& object : registeredObjects) {
    //    //ComponentHandler<Position> position;
    //    //parent->unpack(object, position);

    //    //ComponentHandler<Size> size;
    //    //parent->unpack(object, size);


    //    //ComponentHandler<StaticSprite> staticSprite;
    //    //parent->unpack(object, staticSprite);
    //    //TextureManager::GetSingletonInstance()->draw("Pieces", position->x, position->y, size->width, size->height);

    //}
}

void Piece::onCollisionEvent(CollisionEvent* collision) {
    ComponentHandler<Motion> motionA;
    parent->unpack(collision->objectA, motionA);
    motionA->xVelocity = 0;
    motionA->yVelocity = -3;

    ComponentHandler<Motion> motionB;
    parent->unpack(collision->objectB, motionB);
    motionB->xVelocity = 0;
    motionB->yVelocity = 2;     
}