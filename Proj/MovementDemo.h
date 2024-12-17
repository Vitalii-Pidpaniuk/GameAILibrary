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
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

using namespace std;

class MovementDemo
{
private:
	//Window
	sf::RenderWindow* window;

	//Resources
	map<string, sf::Texture*> textures;
	vector<Bullet*> bullets;

	//GUI
	sf::Font font;
	sf::Text pointText;

	sf::Text gameOverText;

	sf::Text MovementDemoOverText;

	//World
	sf::Texture worldBackgroundTex;
	sf::Sprite worldBackground;


	//Player
	
	Player* player;

	//Systems
	unsigned points;


	//Enemy
	float spawnTimer;
	float spawnTimerMax;

	//PlayerGUI
	sf::RectangleShape playerHpBar;
	sf::RectangleShape playerHpBarBack;

	vector<Enemy*> enemies;

	void initWindow();
	void initTextures();
	//void initPath();
	void initGUI();
	void initWorld();
	void initSystems();
	void initEnemies();

	void initPlayer();
	//void initGraph();

public:
	MovementDemo();
	virtual ~MovementDemo();

	void run();

	void updatePollEvents();
	void updateInput();
	void updateGUI();
	void updateWorld();
	void updateCollision();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void detectAndActOnTargets();
	void update();
	void renderGUI();
	void renderWorld();
	void render();
};

