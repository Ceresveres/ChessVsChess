#pragma once
#include "ComponentMask.h"
#include <vector>

typedef unsigned char* ComponentData;
typedef std::vector<int> ArchetypeID;

struct Archetype
{
    ComponentMask componentMask;
    std::vector<ComponentData> componentData;
    std::vector<uint32_t> entityIds;
    std::vector<std::size_t> componentDataSize;
};