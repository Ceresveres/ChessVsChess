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