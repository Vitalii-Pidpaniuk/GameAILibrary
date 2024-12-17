#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>

class Enemy
{
private:
	sf::Sprite sprite;
	unsigned pointCount;
	sf::CircleShape shape;
	int type;
	float speed;
	float pos_x, pos_y;
	int hp;
	int hpMax;
	int damage;
	int points;

	void initVariables();
	void initShape();

public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();
	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	bool isInFrontOfPlayer(const sf::Vector2f& playerPos, const float& viewDistance);
	const int& getPoints() const;
	const int& getDamage() const;
	void SetPos(float x, float y);
	void update();
	void render(sf::RenderTarget* target);
};

#endif // !ENEMY_H