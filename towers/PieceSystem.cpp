#include "PieceSystem.h"

void Piece::update() {
    for (auto& object : registeredObjects) {
        ComponentHandler<Position> position;
        parent->unpack(object, position);
        position->x += 1;
    }
}

void Piece::draw() {
    int tmpColor[4] = { 16, 143, 50, 255 };
    for (auto& object : registeredObjects) {
        ComponentHandler<Position> position;
        parent->unpack(object, position);

        ComponentHandler<Size> size;
        parent->unpack(object, size);

        int choice = (position->x + position->y) % 200;
        if (choice == 0) {
            tmpColor[0] = 0;
            tmpColor[1] = 143;
            tmpColor[2] = 50;
            tmpColor[3] = 255;
        }
        else {
            tmpColor[0] = 86;
            tmpColor[1] = 201;
            tmpColor[2] = 50;
            tmpColor[3] = 255;
        }

        ComponentHandler<StaticSprite> staticSprite;
        parent->unpack(object, staticSprite);
        TextureManager::GetSingletonInstance()->draw("Pieces", position->x, position->y, size->width, size->height);

    }
}