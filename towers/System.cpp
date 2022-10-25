//#include "System.h"
//
//void System::registerObject(Object const& object) { 
//    registeredObjects.push_back(object); 
//}
//
//void System::unRegisterObject(Object const& object) {
//    for (auto it = registeredObjects.begin(); it != registeredObjects.end(); ++it) {
//        Object e = *it;
//        if (e.id == object.id) {
//            registeredObjects.erase(it);
//            return;
//        }
//    }
//}
//
//ComponentMap System::getSignature() { return signature; }