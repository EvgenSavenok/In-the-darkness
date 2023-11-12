#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Player.h"

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
	const int enemyEye = 10;
	const int enemyStep = 8;
	void checkOnLetWithPlayer(Player& player);
	bool isHasLeftLet;
	bool isHasRightLet;
	bool isHasTopLet;
	bool isHasBottomLet;
	
public:
	sf::Sprite getSprite() { return enemySprite; };
	Enemies(int startX, int startY);
	void setDir(enemyDirection dir) { this->enemyDir = dir; };
	enemyDirection getDir() { return enemyDir; };
	float enemyX, enemyY;
	int returnEnemyX() { return enemyX; }
	int returnEnemyY() { return enemyY; }
	bool enemyMove(sf::Clock clock, Player& player, SoundManager& sound);
	bool checkOnMoveDown(Player& player, int curCol, int curRow, SoundManager& sound);
	bool checkOnMoveUp(Player& player, int curCol, int curRow, SoundManager& sound);
	bool checkOnMoveLeft(Player& player, int curCol, int curRow, SoundManager& sound);
	bool checkOnMoveRight(Player& player, int curCol, int curRow, SoundManager& sound);
	bool checkBoarDown(int curCol, int curRow);
	bool checkBoarUp(int curCol, int curRow);
	bool checkBoarLeft(int curCol, int curRow);
	bool checkBoarRight(int curCol, int curRow);
	void checkOnNearPlayer(Player& player);
	void startKillingAnimation(char dir, Player& player, SoundManager& soundz);
	void determineDir(int curCol, int curRow);
	bool getInteractionWithPlayer() { return isFacedWithPlayer; }
	void setInteractionWithPlayer(bool isFacedWithPlayer) { this->isFacedWithPlayer = isFacedWithPlayer; }
	void checkOnPlayer(Player& player, SoundManager& sound);
	enemyDirection defineNewDirection(int curNumOfDir, int curCol, int curRow);
	sf::Clock enemyClock;
	static const int brickSize = 90;
};