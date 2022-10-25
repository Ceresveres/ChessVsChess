#include "Entity.h"

Entity::Entity(ECS& ecs)
    :
    m_id(ecs.GetNewID()),
    m_ecs(ecs)
{
    m_ecs.RegisterEntity(m_id);
}

Entity::~Entity() {

}

//template<class C>
//C* Entity::Add(C&& c)
//{
//    return m_ecs.AddComponent<C>(m_id, std::forward<C>(c));
//}