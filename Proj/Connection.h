#pragma once
#include "NodeXY.h"
using namespace std;

class Connection
{
public:
	NodeXY from;
	NodeXY to;
	float cost;
    Connection();
    Connection(NodeXY FromNode, NodeXY ToNode, float Cost)
    {
        from = FromNode;
        to = ToNode;
        cost = Cost;
    }
};

