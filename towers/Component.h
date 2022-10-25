#pragma once

#include "ECS.h"

#include "IDgenerator.h"
#include <utility>
#include <cstddef>
#include <iostream>
#include <bit>
#include <new>
#include <string>

class ComponentBase
{
public:
    virtual ~ComponentBase() {}
    virtual void DestroyData(unsigned char* data) const = 0;
    virtual void MoveData(unsigned char* source, unsigned char* destination) const = 0;
    virtual void ConstructData(unsigned char* data) const = 0;
    virtual std::size_t GetSize() const = 0;
};

template<class C>
class Component : public ComponentBase
{
public:
    virtual void DestroyData(unsigned char* data) const override;

    virtual void MoveData(unsigned char* source, unsigned char* destination) const override;

    virtual void ConstructData(unsigned char* data) const override;

    virtual std::size_t GetSize() const override;

    static int GetTypeID();
};

template<class C>
void Component<C>::DestroyData(unsigned char* data) const
{
    C* dataLocation = std::launder(reinterpret_cast<C*>(data));

    dataLocation->~C();
}

template<class C>
void Component<C>::ConstructData(unsigned char* data) const
{
    new (&data[0]) C();
}

template<class C>
void Component<C>::MoveData(unsigned char* source, unsigned char* destination) const
{
    new (&destination[0]) C(std::move(*std::bit_cast<C*>(source)));
}

template<class C>
std::size_t Component<C>::GetSize() const
{
    return sizeof(C);
}


template<class C>
int Component<C>::GetTypeID()
{
    return TypeIdGenerator<ComponentBase>::GetNewID<C>();
}



struct Randomness
{
    float a;
};

struct Position {
    float  x;
    float  y;
};

struct Name {
    std::string name{ "billy" };
};

struct test1 {
    std::string name1{ "billy" };
};

struct test2 {
    std::string name2{ "billy" };
};

struct tester {
    std::string name3{ "billy" };
    int i = 5;
    int b = 50;
};

struct ID {
    int id = 0;
};