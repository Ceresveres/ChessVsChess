#include "PieceSystem.h"

void Piece::init() {
    eventBus = parent->getEventBus();
}

void Piece::update() {
    for (auto& object : registeredObjects) {
        ComponentHandler<Position> position;
        parent->unpack(object, position);
        ComponentHandler<Motion> motion;
        parent->unpack(object, motion);
        ComponentHandler<BoundingBox> boundingBox;
        parent->unpack(object, boundingBox);

        position->x += motion->xVelocity;
        *boundingBox.component += *motion.component;
    }
}

void Piece::draw() {
    int tmpColor[4] = { 16, 143, 50, 255 };
    for (auto& object : registeredObjects) {
        ComponentHandler<Position> position;
        parent->unpack(object, position);

        ComponentHandler<Size> size;
        parent->unpack(object, size);


        ComponentHandler<StaticSprite> staticSprite;
        parent->unpack(object, staticSprite);
        TextureManager::GetSingletonInstance()->draw("Pieces", position->x, position->y, size->width, size->height);

    }
}