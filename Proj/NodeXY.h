#pragma once
#include <vector>
#include <queue>
#include <limits>
#include <List>
#include <string>


using namespace std;

class NodeXY
{
public:
	string name;
	NodeXY() 
	{
		//name = "node";
		position.first = 0;
		position.second = 0;
	};
	NodeXY(int a, int b, string Name)
	{
		name = Name;
		position.first = a;
		position.second = b;
	}

	pair<int, int> position;

	pair<int, int> Get()
	{
		return position;
	}

	void Set(pair<int, int> Position)
	{
		position = Position;
	}

	bool operator==(const NodeXY& other) const {
		return (position.first == other.position.first) && (position.second == other.position.second);
	}

	bool operator<(const NodeXY& other) const {
		if (position.first == other.position.first) {
			return position.second < other.position.second;
		}
		return position.first < other.position.first;
	}

	bool operator!=(const NodeXY& other) const {
		return (position.first != other.position.first) || (position.second != other.position.second);
	}

	struct Hash {
		size_t operator()(const NodeXY& node) const {
			return hash<int>()(node.position.first) ^ hash<int>()(node.position.second);
		}
	};
};

