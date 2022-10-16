#pragma once
#include "componentManager.h"
#include "Object.h"
#include <SDL.h>
#include <string>
#include <cmath>
#include <vector>


struct ComponentCounter {
    static int familyCounter;
};

template <typename ComponentType>
struct Component {
    static inline int family() {
        static int family = ComponentCounter::familyCounter++;
        return family;
    }
};

template <typename C>
static int GetComponentFamily() {
    return Component<typename std::remove_const<C>::type>::family();
}

struct Position : Component<Position> {
    Position(int x, int y) : x(x), y(y) {};
    int x;
    int y;
};

struct Motion : Component<Motion> {
    Motion(int x, int y=0) : xVelocity(x), yVelocity(y) {};
    int xVelocity;
    int yVelocity;
};

struct Layer : Component<Layer> {
    int layerID;
    Layer(int id) : layerID(id) {};
};

//struct Grid : Component<Grid> {
//    SDL_Rect grid;
//    Grid(int x, int y) {
//        grid.x = x;
//        grid.y = y;
//        grid.w = 100;
//        grid.h = 100;
//    };
//};

//struct Dynamic : Component<Dynamic> {
//
//};

struct Size : Component<Size> {
    int width, height;
    Size(int width, int height)
        : width(width), height(height) {}
};

struct StaticSprite : Component<StaticSprite> {
    char textureID[1024];
    StaticSprite(std::string texture="none")
    {
        std::snprintf(textureID, sizeof(textureID), "%s", texture.c_str());
    }
};

struct BoundingBox : Component<BoundingBox> {
    SDL_Rect grid;
    BoundingBox(int x, int y, int w, int h) {
        grid.x = x;
        grid.y = y;
        grid.w = w;
        grid.h = h;
    };

    BoundingBox& operator+=(const Motion& rhs) {
        this->grid.x += rhs.xVelocity;
        this->grid.y += rhs.yVelocity;
        return *this;
    }
};