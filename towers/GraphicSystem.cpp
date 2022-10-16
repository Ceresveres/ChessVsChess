#include "GraphicSystem.h"

void GraphicSystem::update() {
    //for (auto& object : registeredObjects) {
    //    ComponentHandler<Position> position;
    //    parent->unpack(object, position);

    //    ComponentHandler<Position> position;
    //    parent->unpack(object, position);
    //}
}

void GraphicSystem::registerObject(Object const& object) {
    ComponentHandler<Layer> layer;
    parent->unpack(object, layer);
    registeredLayers[layer->layerID].push_back(object);
}

void GraphicSystem::draw() {
    int tmpColor[4] = { 16, 143, 50, 255 };
    for (auto& layer : registeredLayers) {
        for (auto& object : layer.second) {
            ComponentHandler<BoundingBox> grid;
            ComponentHandler<StaticSprite> sprite;
            parent->unpack(object, grid, sprite);

            if (strcmp(sprite->textureID, "none") == 0) {
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
                TextureManager::GetSingletonInstance()->draw(grid->grid, tmpColor);

            }
            else {
                TextureManager::GetSingletonInstance()->draw(sprite->textureID, grid->grid);
            }
        }
    }
}
