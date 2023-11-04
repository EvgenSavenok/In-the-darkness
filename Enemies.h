#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Players.h"

enum class enemyDirection { down, up, left, right, none };

class Enemies
{
private:
	sf::Image enemyImg;
	sf::Texture enemyTexture;
	sf::Sprite enemySprite;
	enemyDirection enemyDir;
	int curEnemyImg;
	int curKillingImg = 0;
	float delayInSeconds = 0.2f;
	Map map;
	bool isFacedWithPlayer = false;
	bool isFacedWithLet = false;
	const int curEnemyX = 2;
	const int curEnemyY = 11;
	const int enemyEye = 5;
	
public:
	sf::Sprite getSprite() { return enemySprite; };
	Enemies();
	void setDir(enemyDirection dir) { this->enemyDir = dir; };
	enemyDirection getDir() { return enemyDir; };
	float enemyX, enemyY;
	int returnEnemyX() { return enemyX; }
	int returnEnemyY() { return enemyY; }
	bool enemyMove(sf::Clock clock, Player& player);
	bool checkOnMoveDown(Player& player);
	bool checkOnMoveUp(Player& player);
	bool checkOnMoveLeft(Player& player);
	bool checkOnMoveRight(Player& player);
	bool checkBoarDown();
	bool checkBoarUp();
	bool checkBoarLeft();
	bool checkBoarRight();
	void checkOnNearPlayer(Player& player);
	void startKillingAnimation(char dir, Player& player);
	void determineDir();
	bool getInteractionWithPlayer() { return isFacedWithPlayer; }
	void setInteractionWithPlayer(bool isFacedWithPlayer) { this->isFacedWithPlayer = isFacedWithPlayer; }
	void checkOnPlayer(Player& player);
	enemyDirection defineNewDirection(int curNumOfDir);
	sf::Clock enemyClock;
	static const int brickSize = 90;
};