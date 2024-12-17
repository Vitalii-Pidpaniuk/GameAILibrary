#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <cmath>
#include <limits>
#include <algorithm>
#include "Graph.h"
#include "NodeValues.h"

using namespace std;

class AStarPathfinding {
private:
    float CountHCost(NodeXY start, NodeXY goal) {
        return sqrt(pow(start.position.first - goal.position.first, 2) + pow(start.position.second - goal.position.second, 2)); // Евристика Евкліда
    }

    unordered_map<NodeXY, NodeValues, NodeXY::Hash> nodes;

public:
    list<NodeXY>* FindPath(Graph graph, NodeXY startNode, NodeXY goal) {
        priority_queue<pair<float, NodeXY>, vector<pair<float, NodeXY>>, greater<pair<float, NodeXY>>> openSet;
        unordered_map<NodeXY, bool, NodeXY::Hash> closedSet;

        openSet.push({ 0, startNode });
        nodes[startNode] = NodeValues(NodeXY(), 0, CountHCost(startNode, goal));

        while (!openSet.empty()) {
            NodeXY currentNode = openSet.top().second;
            openSet.pop();

            if (currentNode == goal) {
                return RetracePath(currentNode);
            }

            closedSet[currentNode] = true;

            for (auto connection : graph.GetConnections(currentNode)) {
                
                NodeXY neighbor = connection.to;
                if (closedSet.find(neighbor) != closedSet.end()) {
                    continue;
                }
                float newGCost = nodes[currentNode].gCost + connection.cost;
                if (nodes.find(neighbor) == nodes.end() || newGCost < nodes[neighbor].gCost) {
                    nodes[neighbor] = NodeValues(currentNode, newGCost, CountHCost(neighbor, goal));
                    openSet.push({ nodes[neighbor].fCost(), neighbor });
                }
            }
        }

        return {};
    }

private:
    list<NodeXY>* RetracePath(NodeXY endNode) {
        list<NodeXY>* path = new list<NodeXY>();
        NodeXY currentNode = endNode;

        while (nodes[currentNode].parent != NodeXY()) {
            path->push_back(currentNode);
            currentNode = nodes[currentNode].parent;
        }
        path->push_back(currentNode);
        reverse(path->begin(), path->end());

        return path;
    }
};