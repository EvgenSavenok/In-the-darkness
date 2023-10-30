#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

enum class enemyDirection { down, up, left, right, none };

class Enemies
{
private:
	sf::Image img;
	sf::Texture texture;
	sf::Sprite sprite;
	enemyDirection dir;
	int curImg;
	float delayInSeconds = 0.2f;
	Map map;
	
public:
	sf::Sprite getSprite() { return sprite; };
	Enemies();
	void setDir(enemyDirection dir) { this->dir = dir; };
	enemyDirection getDir() { return dir; };
	float x, y;
	int returnEnemyX() { return x; }
	int returnEnemyY() { return y; }
	bool enemyMove(sf::Clock clock);
	bool checkOnMoveDown();
	bool checkOnMoveUp();
	bool checkOnMoveLeft();
	bool checkOnMoveRight();
	bool checkBoarDown();
	bool checkBoarUp();
	bool checkBoarLeft();
	bool checkBoarRight();
	bool checkOnNearPlayer();
	void determineDir();
	enemyDirection defineNewDirection(int curNumOfDir);
	sf::Clock enemyClock;
	static const int brickSize = 90;
};