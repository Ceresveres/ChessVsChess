#pragma once
#include <vector>
#include <map>
#include "Object.h"
#include "ComponentMap.h"

class SpatialHashing {
    int gridSize;
    int cellSize;
    int cellsBySide; // gridSize / cellSize
    int buckets; // cellsBySide * cellsBySide
    float conversionFactor; // 1f / cellSize

    std::vector<Object> registeredObjects;
    std::map<int, std::initializer_list<Object>> hashtable;

    SpatialHashing(int gridSize, int cellSize) : gridSize(gridSize),
        cellSize(cellSize),
        cellsBySide(gridSize / cellSize),
        buckets(cellsBySide* cellsBySide),
        conversionFactor(1.0 / cellSize)
    {
    };
};