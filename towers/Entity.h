#pragma once

#include "ECS.h"
#include "Entity.h"
#include <utility>

class ECS;
class Entity
{
public:
    explicit Entity(ECS& ecs);
    ~Entity();

    //template<class C, typename... Args>
    //C* Add(Args&&... args)
    //{
    //    //return m_ecs.AddComponent<C>(m_id, std::forward<Args>(args)...);
    //}
    template<class C, typename... Args>
    C* Add(Args&&... args);

    template<class C>
    C* Add(C&& c);

    int GetID() const
    {
        return m_id;
    }

private:
    uint32_t  m_id;
    ECS& m_ecs;
};

template<class C>
C* Entity::Add(C&& c)
{
    return m_ecs.AddComponent<C>(m_id, std::forward<C>(c));
}

template<class C, typename... Args>
C* Entity::Add(Args&&... args)
{
    return m_ecs.AddComponent<C>(m_id, std::forward<Args>(args)...);
}