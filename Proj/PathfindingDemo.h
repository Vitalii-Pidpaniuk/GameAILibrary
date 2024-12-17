#pragma once
#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "AStarPathfinding.h"
#include "DijkstraPathfinding.h"
using namespace std;

class PathfindingDemo
{
private:
	//Window
	sf::RenderWindow* window;

	//Resources
	map<string, sf::Texture*> textures;
	
	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text PathfindingDemoOverText;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;

	//Systems
	//unsigned points;

	//pathfinding
	list<NodeXY> path;
	Graph graph;

	//Enemy
//	float spawnTimer;
//	float spawnTimerMax;

	void initWindow();
	void initTextures();
	void initPath();
	void initGUI();
	void initWorld();
	void initSystems();

	//void initPlayer();
	void initGraph();

public:
	PathfindingDemo();
	virtual ~PathfindingDemo();

	void run();
	void SetGraph(Graph Graph);

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void update();
	void renderGUI();
	void renderWorld();
	void render();
};
