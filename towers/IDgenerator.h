#include <cstdint>
#pragma once
typedef std::uint32_t IDType;

template<class T>
class TypeIdGenerator
{
private:

    static IDType count;

public:

    template<class U>
    static const IDType GetNewID()
    {
        static const IDType idCounter = count++;
        return idCounter;
    }
};

template<class T> IDType TypeIdGenerator<T>::count = 0;