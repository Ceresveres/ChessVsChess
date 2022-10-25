#pragma once
#include "Component.h"

struct ComponentMask {
    unsigned int mask = 0;

    template <class C>
    void addComponent() {
        mask |= (1 << Component<C>::GetTypeID());
    }

    template <class C>
    void addComponents() {
        mask |= (1 << Component<C>::GetTypeID());
    }

    template <class C, class T, class... Cs>
    void addComponents() {
        mask |= (1 << Component<C>::GetTypeID());
        addComponents<T>();
        addComponents<T, Cs...>();
    }

    template <class C>
    void removeComponent() {
        mask &= ~(1 << Component<C>::GetTypeID());
    }

    template <class C>
    bool hasComponent() {
        return mask & (1 << Component<C>::GetTypeID());
    }

    bool hasComponent(const int id) {
        return mask & (1 << id);
    }

    bool getComponentID(const int bit) {
        return mask & (1 << (bit - 1));
    }

    bool isNewMatch(ComponentMask oldMask, ComponentMask systemMask) {
        return matches(systemMask) && !oldMask.matches(systemMask);
    };

    bool isNoLongerMatched(ComponentMask oldMask, ComponentMask systemMask) {
        return oldMask.matches(systemMask) && !matches(systemMask);
    };

    bool matches(ComponentMask systemMask) {
        return ((mask & systemMask.mask) == systemMask.mask);
    };

    bool isExactMatch(ComponentMask archMask, ComponentMask systemMask) {
        return (archMask.mask == systemMask.mask);
    }
};