#pragma once
#include <vector>
#include <queue>
#include <limits>
#include <List>
#include "NodeXY.h"
#include "Connection.h"
using namespace std;


class NodeRecord
{
public:
	NodeXY node;
	Connection* connection;
	float CostSoFar;
	NodeRecord* ParentNode;

	NodeRecord() : node(), connection(), ParentNode(nullptr), CostSoFar(0.0f) {}

	NodeRecord(NodeXY node, Connection* connection, NodeRecord* parentNode, float costSoFar)
		: node(node), connection(connection), ParentNode(parentNode), CostSoFar(costSoFar) {}

	
};

