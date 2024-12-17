#include "Enemy.h"

void Enemy::initVariables()
{
	this->pointCount = rand() % 8 + 3;
	this->type    = 0;
	this->speed   = static_cast<float> (this->pointCount/3);
	this->hpMax   = static_cast<int> (this->pointCount);
	this->hp      = this->hpMax;
	this->damage  = this->pointCount;
	this->points  = this->pointCount;
}

void Enemy::initShape()
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1, 255));
}

Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariables();
	this->initShape();
	this->shape.setPosition(pos_x, pos_y);
}

const sf::Vector2f& Enemy::getPos() const
{
	return this->shape.getPosition();
}

Enemy::~Enemy()
{
}

const sf::FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;
}

void Enemy::SetPos(float x, float y)
{
	pos_x = x;
	pos_y = y;
}

// Додати метод для перевірки, чи ворог знаходиться перед гравцем
bool Enemy::isInFrontOfPlayer(const sf::Vector2f& playerPos, const float& viewDistance)
{
	sf::Vector2f enemyPos = this->getPos();
	sf::Vector2f direction = enemyPos - playerPos;

	// Перевірка, чи ворог знаходиться в межах визначеного поля зору
	return (std::abs(direction.x) < viewDistance && direction.y > 0.f);
}

void Enemy::update()
{
	this->shape.move(0.f, this->speed);
	this->SetPos(sprite.getPosition().x, sprite.getPosition().y);
}

void Enemy::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
