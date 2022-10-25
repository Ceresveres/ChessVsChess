//#include "PieceSystem.h"
//
//void Piece::init() {
//    eventBus = parent->getEventBus();
//    eventBus->subscribe(this, &Piece::onCollisionEvent);
//}
//
//void Piece::update() {
//    for (auto& object : registeredObjects) {
//        ComponentHandler<Motion> motion;
//        ComponentHandler<BoundingBox> boundingBox;
//
//        parent->unpack(object, motion, boundingBox);
//
//        *boundingBox.component += *motion.component;
//
//        if (boundingBox->grid.x >= 500) {
//            eventBus->publish(new SpawnEvent(object));
//        }
//    }
//}
//
//void Piece::draw() {
//
//}
//
//void Piece::onCollisionEvent(CollisionEvent* collision) {
//    ComponentHandler<Motion> motionA;
//    parent->unpack(collision->objectA, motionA);
//    motionA->xVelocity = 0;
//    motionA->yVelocity = -3;
//
//    ComponentHandler<Motion> motionB;
//    parent->unpack(collision->objectB, motionB);
//    motionB->xVelocity = 0;
//    motionB->yVelocity = 2;     
//}