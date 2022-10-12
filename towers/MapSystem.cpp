#include "MapSystem.h"

void Map::update() {

}

void Map::draw() {
    int tmpColor[4] = { 16, 143, 50, 255 };
    for (auto& object : registeredObjects) {
        ComponentHandler<Grid> grid;
        parent->unpack(object, grid);

        int choice = (grid->grid.x + grid->grid.y) % 200;
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

        parent->unpack(object, grid);
        TextureManager::GetSingletonInstance()->drawTemp(grid->grid, tmpColor);

    }
}