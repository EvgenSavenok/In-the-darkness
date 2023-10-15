#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

enum class enemyDirection { down, up, left, right };

class Enemies
{
private:
	sf::Image img;
	sf::Texture texture;
	sf::Sprite sprite;
	enemyDirection dir;
	int curImg;
	float delayInSeconds = 0.2f;
	
public:
	sf::Sprite getSprite() { return sprite; };
	Enemies();
	void setDir(enemyDirection dir) { this->dir = dir; };
	float x, y;
	int returnEnemyX() { return x; }
	int returnEnemyY() { return y; }
	bool enemyMove(sf::Clock clock);
	bool checkOnMoveDown();
	bool checkOnMoveUp();
	bool checkOnMoveLeft();
	bool checkOnMoveRight();
	sf::Clock enemyClock;
	static const int brickSize = 90;
};