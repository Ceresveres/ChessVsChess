#include "ECS.h"

ECS::ECS() : entityIdCounter(1)
{}

ECS::~ECS() {
    for (Archetype* archetype : archetypes)
    {
        auto componentMask = archetype->componentMask.mask;
        for (int i = std::popcount(componentMask) - 1; componentMask > 0; --i) {
            const ComponentBase* const comp = componentMap[i];
            const std::size_t& dataSize = comp->GetSize();
            for (std::size_t e = 0; e < archetype->entityIds.size(); ++e)
            {
                comp->DestroyData(&archetype->componentData[i][e * dataSize]);
            }
            delete[] archetype->componentData[i];
            componentMask = (componentMask % std::bit_floor(componentMask));
        }
        delete archetype;
    }

    for (ComponentTypeIDBaseMap::value_type& p : componentMap)
        delete p.second;
}

void ECS::RegisterEntity(const uint32_t entityId)
{
    entityArchetypeMap[entityId] = Record(nullptr, 0);

}

int ECS::GetNewID() {
    return entityIdCounter++;
};

Archetype* ECS::GetArchetype(const ComponentMask& compMask)
{
    for (Archetype* archetype : archetypes)
    {
        if (archetype->componentMask.isExactMatch(archetype->componentMask, compMask)) {
            return archetype;
        }
    }

    Archetype* newArchetype = new Archetype;
    newArchetype->componentMask = compMask;
    archetypes.push_back(newArchetype);
    for (ArchetypeID::size_type i = compMask.mask; i; i &= i - 1) {
        // assigns data size to 0, and allocates char array of size 0
        newArchetype->componentData.push_back(new unsigned char[0]);
        newArchetype->componentDataSize.push_back(0);
    }

    return newArchetype;
}

void ECS::RegisterSystem(const std::uint8_t& layer, SystemBase* system)
{
    systems[layer].push_back(system);
}

void ECS::RunSystems(const std::uint8_t& layer, const float elapsedMilliseconds)
{
    //auto tes  = systems[layer];
    for (auto* system : systems[layer])
    {
        const ComponentMask& key = system->GetMask();

        for (Archetype* archetype : archetypes)
        {
            if (((key.mask & archetype->componentMask.mask) == key.mask) && !archetype->entityIds.empty()) {
                system->DoAction(elapsedMilliseconds, archetype);
            }
            //if (std::includes(archetype->type.begin(), archetype->type.end(),
            //    key.begin(), key.end()))
            //{
            //    // this archetype has all the types required by the system
            //    // so we can pull it's relevant data, reinterpret them as
            //    // their correct types, and call the Func in the system
            //}
        }
    }
}

bool ECS::HasEntity(const uint32_t& entityId) {
    return entityArchetypeMap.contains(entityId);
}


void ECS::RemoveEntity(const uint32_t& entityId)
{
    if (!entityArchetypeMap.contains(entityId))
        return; // it doesn't exist

    auto& record = entityArchetypeMap[entityId];
    auto* oldArchetype = record.archetype;

    if (!oldArchetype)
    {
        entityArchetypeMap.erase(entityId);
        return;
    }

    auto compMask = oldArchetype->componentMask.mask;


    //for (int i = std::popcount(oldComponentMask) - 1, j = i - 1; oldComponentMask > 0; --i) {
    //    const auto& componentID = std::bit_width(oldComponentMask) - 1;
    //    const auto* const comp = componentMap[componentID];
    //    
    //    const auto& compSize = comp->GetSize();

    //    comp->DestroyData(&oldArchetype->componentData[i][record.index * compSize]);
    //}

    auto entityIndex = std::find(oldArchetype->entityIds.begin(),
        oldArchetype->entityIds.end() - 1,
        entityId) - oldArchetype->entityIds.begin();

    auto lastEntity = oldArchetype->entityIds.size() - 1;

    for (int i = std::popcount(compMask) - 1; compMask > 0; --i) {
        const auto& componentID = std::bit_width(compMask) - 1;
        const ComponentBase* const oldComp = componentMap[componentID];
        const std::size_t& oldCompDataSize = oldComp->GetSize();

        oldArchetype->componentDataSize[i] -= oldCompDataSize;

        oldComp->MoveData(&oldArchetype->componentData[i][lastEntity * oldCompDataSize],
            &oldArchetype->componentData[i][entityIndex * oldCompDataSize]);

        oldComp->DestroyData(&oldArchetype->componentData[i][lastEntity * oldCompDataSize]);

        compMask = (compMask % std::bit_floor(compMask));
    }

    std::swap(oldArchetype->entityIds[entityIndex], oldArchetype->entityIds[lastEntity]);
    oldArchetype->entityIds.pop_back();
    entityArchetypeMap.erase(entityId);
    record.index = oldArchetype->entityIds.size() - 1;
    record.archetype = oldArchetype;
}