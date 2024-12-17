#pragma once
#include "NodeXY.h"

class NodeValues {
public:
    NodeXY parent;
    float gCost;
    float hCost;

    NodeValues(NodeXY parent = NodeXY(), float gCost = 0, float hCost = 0)
        : parent(parent), gCost(gCost), hCost(hCost) {}

    float fCost() const {
        return gCost + hCost;
    }
};

