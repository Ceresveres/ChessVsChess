//#include "GraphicSystem.h"
//
//void GraphicSystem::update() {
//    //for (auto& object : registeredObjects) {
//    //    ComponentHandler<Position> position;
//    //    parent->unpack(object, position);
//
//    //    ComponentHandler<Position> position;
//    //    parent->unpack(object, position);
//    //}
//}
//
//void GraphicSystem::registerObject(Object const& object) {
//    ComponentHandler<Layer> layer;
//    parent->unpack(object, layer);
//    registeredLayers[layer->layerID].push_back(object);
//}
//
//void GraphicSystem::draw() {
//    int tmpColor[4] = { 16, 143, 50, 255 };
//    for (auto& layer : registeredLayers) {
//        for (auto& object : layer.second) {
//            ComponentHandler<BoundingBox> grid;
//            ComponentHandler<StaticSprite> sprite;
//            parent->unpack(object, grid, sprite);
//            if (sprite->currentRow != -1) {
//                TextureManager::GetSingletonInstance()->draw(sprite->textureID, grid->grid, sprite->currentRow, sprite->currentFrame);
//            }
//            else {
//                TextureManager::GetSingletonInstance()->draw(sprite->textureID, grid->grid);
//            }
//        }
//    }
//}
