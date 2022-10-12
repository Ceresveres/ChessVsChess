#pragma once
#include "component.h"

struct ComponentMap {
    unsigned int mask = 0;

    template <typename ComponentType>
    void addComponent() {
        mask |= (1 << GetComponentFamily<ComponentType>());
    }

    template <typename ComponentType>
    void removeComponent() {
        mask &= ~(1 << GetComponentFamily<ComponentType>());
    }

    bool isNewMatch(ComponentMap oldMask, ComponentMap systemMask) {
        return matches(systemMask) && !oldMask.matches(systemMask);
    };

    bool isNoLongerMatched(ComponentMap oldMask, ComponentMap systemMask) {
        return oldMask.matches(systemMask) && !matches(systemMask);
    };

    bool matches(ComponentMap systemMask) {
        return ((mask & systemMask.mask) == systemMask.mask);
    };
};