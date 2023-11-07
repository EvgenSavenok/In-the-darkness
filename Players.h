#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animations.h"
#include "Boxes.h"

enum class Direction { down, up, left, right };

class Player
{
private:
	sf::Image playerImg;
	sf::Texture texture;
	sf::Sprite sprite;

	sf::Image deadPlayerImg;
	sf::Texture deadPlayerTexture;
	sf::Sprite deadPlayerSprite;

	Direction playerDir;
	int curImg;
	float delayInSeconds = 0.5f;
	#define numOfBoxes 7
	bool key;
	bool canPushBox[numOfBoxes];

	sf::Image keyImg;
	sf::Texture keyTexture;
	sf::Sprite keySprite;

	sf::Image lifeBarImg;
	sf::Texture lifeBarTexture;
	sf::Sprite lifeBarSprite;

	bool checkOnDownBoxCollisions(int curRow, int curCol, Boxes& box, Map& map);
	bool checkOnUpBoxCollisions(int curRow, int curCol, Boxes& box, Map& map);
	bool checkOnLeftBoxCollisions(int curRow, int curCol, Boxes& box, Map& map);
	bool checkOnRightBoxCollisions(int curRow, int curCol, Boxes& box, Map& map);
	void checkBoxOnWallCollision(Map& map, int curBoxRow, int curBoxCol, char dir, int indexOfBox, Boxes& box);

	const float playerStep = 4;
	const int playerDelay = 1;

	const int rowOffset = 2;
	const int colOffset = 2;

	bool isGameOver = false;
	int startNumOfLives = 5;
	int numOfLives = 5;
	float widthOfLifeBar = 280;

public:
	sf::Sprite getSprite() { return sprite; };
	Player();
	bool move(sf::RenderWindow& window, Map& map, Animations& animeOfTeleport, Boxes& box, Animations& cage, sf::Clock& playerClock);
	void setDir(Direction dir) { this->playerDir = dir; };
	bool update(sf::Clock clock, Map& map, sf::Clock teleportClock, Animations& animeOfTeleport, sf::RenderWindow& window, sf::View& camera);
	float playerX, playerY;
	bool checkOnMoveDown(Boxes& box, Animations& cage, Map& map, sf::RenderWindow& window);
	bool checkOnMoveUp(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window);
	bool checkOnMoveLeft(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window);
	bool checkOnMoveRight(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window);
	void updateRight(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window);
	void updateLeft(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window);
	void updateUp(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window);
	void updateDown(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window);
	float returnPlayerX() { return playerX; }
	float returnPlayerY() { return playerY; }
	bool isHasKey() { return key; };
	void setKey(bool key) { this->key = key; };
	void checkOnKey(int curRow, int curCol, char curDir);
	bool checkOnTeleport(Map& map);
	int calculateCurPlayerRow();
	int calculateCurPlayerCol();
	bool prepareForTeleportAnime(Animations& animeOfTeleport, Map& map, sf::Clock teleportClock, bool isNewCycle);
	bool startTeleportAnimation(Map& map, sf::Clock clock, Animations& animeOfTeleport);
	int keyX, keyY;
	int returnKeyX() { return keyX; }
	int returnKeyY() { return keyY; }
	void drawKey(sf::RenderWindow& window);
	void checkOnBox(int curRow, int curCol, char dir, Boxes& box, Map& map, int indexOfBox);
	void checkOnNearBox(int curRow, int curCol, char dir, Boxes& box, Map& map, int indexOfBox);
	bool checkOnRightCageCollision(int curRow, int curCol, bool canMoveRigth, Map map);
	bool checkOnDownCageCollision(bool canMoveDown, Animations& cage, Map map);
	void checkOnDoor(char dir, Map& map, Animations& doorAnime);
	void checkOnBottomDoor(int curRow, int curCol, Map& map, Animations& doorAnime);
	void checkOnTopDoor(int curRow, int curCol, Map& map, Animations& doorAnime);
	void checkOnLeftDoor(int curRow, int curCol, Map& map, Animations& doorAnime);
	void checkOnRightDoor(int curRow, int curCol, Map& map, Animations& doorAnime);
	bool getGameOverState() { return isGameOver; };
	void setGameOverState(bool isGameOver) { this->isGameOver = isGameOver; };
	int getLives() { return numOfLives; };
	void setLives(int numOfLives) { this->numOfLives = numOfLives; };
	void checkLives();
	void drawLives(sf::RenderWindow& window, sf::View& camera);
	sf::Sprite getLifeBarSprite() { return lifeBarSprite; };
	static const int brickSize = 90;
};