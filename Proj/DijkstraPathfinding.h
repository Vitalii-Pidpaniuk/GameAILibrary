#pragma once
#include <vector>
#include <queue>
#include <limits>
#include <List>
#include <iterator>
#include <iostream>
#include <algorithm>
#include "NodeXY.h"
#include "Connection.h"
#include "Graph.h"
#include "NodeRecord.h"
using namespace std;

class DijkstraPathfinding
{
private:
	list<NodeXY>* ReconstructPath(NodeXY start, NodeRecord endNodeRecord)
	{
		cout << "Reconstruct path flag 1\n";
		list<NodeXY>* path = new list<NodeXY>();
		while (endNodeRecord.ParentNode != nullptr)
		{
			cout << "reconstructing...\n";
			path->push_back(endNodeRecord.node);
			endNodeRecord = *endNodeRecord.ParentNode;
		}
		path->push_back(start);
		path->reverse();
		return path;
	}

public:
	list<NodeXY>* FindPath(Graph graph, NodeXY start, NodeXY goal) {
		list<NodeRecord>* open = new list<NodeRecord>;
		list<NodeRecord>* closed = new list<NodeRecord>;

		NodeRecord startRecord(start, nullptr, nullptr, 0);
		open->push_back(startRecord);

		while (!open->empty()) {
			ShowList(*open);
			// «находимо вузол з найменшою варт≥стю
			NodeRecord currant = GetLeastRecord(*open);

			// якщо дос€гнуто мети, в≥дновлюЇмо шл€х
			if (currant.node == goal) {
				return ReconstructPath(start, currant);
			}

			// ќтримуЇмо вс≥ списки з'Їднань поточного вузла
			list<Connection> connectionsLists = graph.GetConnections(currant.node);

			// ѕроходимо через кожен список з'Їднань
			for (auto connection : connectionsLists) {
				NodeXY endNode = connection.to;
				float endNodeCost = currant.CostSoFar + connection.cost;

				if (CheckForElement(*closed, endNode)) {
					continue;
				}

				// «находимо вузол у open, €кщо в≥н уже там
				NodeRecord* existingRecord = FindElement(*open, endNode);

				if (existingRecord != nullptr) {
					// якщо варт≥сть новоњ дороги б≥льше чи р≥вна, пропускаЇмо
					if (existingRecord->CostSoFar <= endNodeCost) {
						continue;
					}
				}
				else {
					// якщо вузла немаЇ в open, створюЇмо новий запис
					closed->push_back(currant);
					NodeRecord* parentNode = &closed->back();
					NodeRecord newRecord(endNode, &connection, parentNode, endNodeCost);
					open->push_back(newRecord);
				}
				
			}

			// ¬идал€Їмо поточний вузол з open ≥ додаЇмо до closed
			list<NodeRecord>::iterator iter = FindElementPosition(*open, currant.node);
			if (iter != open->end()) {
				open->erase(iter);
			}
			closed->push_back(currant);
		}

		return nullptr; // Ўл€х не знайдено
	}


	NodeRecord GetLeastRecord(list<NodeRecord>& list)
	{
		NodeRecord minRec;
		minRec = list.front();
		for (NodeRecord rec : list)
		{
			if (minRec.CostSoFar < rec.CostSoFar)
			{
				minRec = rec;
			}
		}
		return minRec;
	}

	bool CheckForElement(list<NodeRecord> list, NodeXY element)
	{
		for (NodeRecord el : list)
		{
			if (el.node == element)
			{
				return true;
			}
		}
		return false;
	}

	NodeRecord* FindElement(list<NodeRecord> list, NodeXY element)
	{
		for (NodeRecord el : list)
		{
			if (el.node == element)
			{
				return &el;
			}
		}
		return nullptr;
	}


	list<NodeRecord>::iterator FindElementPosition(list<NodeRecord>& List, const NodeXY& Element)
	{
		cout << "Finding position...\n";
		for (auto iter = List.begin(); iter != List.end(); ++iter)
		{
			cout << "Checking node...\n";
			if (iter->node == Element)
			{
				cout << "Node found!\n";
				return iter;
			}
		}
		return List.end();
	}

	void ShowList(const list<NodeRecord>& list)
	{
		for (auto record : list)
		{
			cout << record.node.Get().first << " " << record.node.Get().second << endl;
		}
	}
};