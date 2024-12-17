#pragma once
#include <vector>
#include <queue>
#include <limits>
#include <List>
#include <map>
#include "NodeXY.h"
#include "Connection.h"
using namespace std;

class Graph
{
public:
	map<NodeXY, list<Connection>> connections;

	Graph()
	{
		map<NodeXY, list<Connection>> *connections = new map<NodeXY, list<Connection>>();
	}

	list<Connection> GetConnections(NodeXY node)
	{
		auto it = connections.find(node);
		if (it != connections.end())
		{
			return it->second;
		}

		return list<Connection>();
	}

	void AddConnection(NodeXY from, NodeXY to, float cost)
	{
		if (connections.find(from) == connections.end())
		{
			connections[from] = list<Connection>();
		}
		connections[from].push_back(Connection(from, to, cost));
	}
};
