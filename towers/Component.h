#pragma once
#include "componentManager.h"
#include "Object.h"
#include <SDL.h>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

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

struct Grid : Component<Grid> {
    SDL_Rect grid;
    Grid(int x, int y) {
        grid.x = x;
        grid.y = y;
        grid.w = 100;
        grid.h = 100;
    };
};

struct Size : Component<Size> {
    int width, height;
    Size(int width, int height)
        : width(width), height(height) {}
};

struct StaticSprite : Component<StaticSprite> {
    char textureID[1024];
    StaticSprite(std::string texture)
    {
        std::snprintf(textureID, sizeof(textureID), "%s", texture.c_str());
    }
};
