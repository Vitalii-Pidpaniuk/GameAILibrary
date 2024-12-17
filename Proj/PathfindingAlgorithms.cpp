#include "PathfindingAlgorithms.h"
//#include <iostream>
//#include "Graph.h"

//using namespace std;

//oid Dijkstra()
//{
//    Graph myTestGraph(6);
//    myTestGraph.AddEdge(1, 2, 5);
//    myTestGraph.AddEdge(1, 3, 2);
//    myTestGraph.AddEdge(2, 3, 1);
//    myTestGraph.AddEdge(2, 4, 4);
//    myTestGraph.AddEdge(2, 5, 2);
//    myTestGraph.AddEdge(3, 5, 7);
//    myTestGraph.AddEdge(4, 5, 6);
//    myTestGraph.AddEdge(4, 6, 3);
//    myTestGraph.AddEdge(5, 6, 1);
//
//    vector<int> distances = myTestGraph.Dijkstra(1, 6);
//
//    cout << "Shortest distances from vertex " << "1" << ":\n";
//    for (int i = 0; i < distances.size(); ++i) {
//        if (distances[i] == numeric_limits<int>::max()) {
//            cout << "Vertex " << i << ": Unreachable\n";
//        }
//        else {
//            cout << "Vertex " << i << ": " << distances[i] << "\n";
//        }
//    }
//}
//
//void AStarPathfinding()
//{
//    cout << "A*\n";
//}