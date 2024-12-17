#include <iostream>
#include <SFML/Graphics.hpp>
//#include "GameAILibrary.h"
#include "Graph.h"
#include "NodeXY.h"
#include "PathfindingDemo.h"
#include "MovementDemo.h"
using namespace std;


int main()
{
	//Graph graph;
	srand(time(0));
	//PathfindingDemo demo;
	MovementDemo demo1;
    //demo.SetGraph(graph);
	demo1.run();
    return 0;
}