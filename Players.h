#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Animations.h"
#include "Boxes.h"

enum class Direction { down, up, left, right };

class Players
{
private:
	sf::Image img;
	sf::Texture texture;
	sf::Sprite sprite;

	Direction dir;
	int curImg;
	float delayInSeconds = 0.5f;
	bool key;
	bool canPushBox[7];

	sf::Image keyImg;
	sf::Texture keyTexture;
	sf::Sprite keySprite;

	const float offset = 4;

public:
	sf::Sprite getSprite() { return sprite; };
	Players();
	void move(sf::RenderWindow& window, Map& map, Animations& animeOfTeleport, Boxes& box, Animations& cage);
	void setDir(Direction dir) { this->dir = dir; };
	bool update(sf::Clock clock, Map& map, sf::Clock teleportClock, Animations& animeOfTeleport);
	float x, y;
	bool checkOnMoveDown(Boxes& box, Animations& cage, Map& map);
	bool checkOnMoveUp(Boxes& box, Animations& anime, Map& map);
	bool checkOnMoveLeft(Boxes& box, Animations& anime, Map& map);
	bool checkOnMoveRight(Boxes& box, Animations& anime, Map& map);
	void updateRight(Boxes& box, Animations& anime, Map& map);
	void updateLeft(Boxes& box, Animations& anime, Map& map);
	void updateUp(Boxes& box, Animations& anime, Map& map);
	void updateDown(Boxes& box, Animations& anime, Map& map);
	float returnPlayerX() { return x; }
	float returnPlayerY() { return y; }
	bool isHasKey() { return key; };
	void setKey(bool key) { this->key = key; };
	void checkOnKey(int curRow, int curCol, int curDir);
	bool checkOnTeleport(Map& map);
	int calculateCurRow();
	int calculateCurCol();
	bool prepareForTeleportAnime(Animations& animeOfTeleport, Map& map, sf::Clock teleportClock, bool isNewCycle);
	bool startTeleportAnimation(Map& map, sf::Clock clock, Animations& animeOfTeleport);
	int keyX, keyY;
	int returnKeyX() { return keyX; }
	int returnKeyY() { return keyY; }
	void drawKey(sf::RenderWindow& window);
	void checkOnBox(int curRow, int curCol, char dir, Boxes& box, Map& map, int indexOfBox);
	void checkOnNearBox(int curRow, int curCol, char dir, Boxes& box, Map& map, int indexOfBox);
	bool checkOnRightCageCollision(int curRow, int curCol, bool canMoveRigth);
	bool checkOnDownCageCollision(bool canMoveDown);
	void checkOnDoor(char dir, Map& map, Animations& doorAnime);
	void checkOnBottomDoor(int curRow, int curCol, Map& map, Animations& doorAnime);
	void checkOnTopDoor(int curRow, int curCol, Map& map, Animations& doorAnime);
	void checkOnLeftDoor(int curRow, int curCol, Map& map, Animations& doorAnime);
	void checkOnRightDoor(int curRow, int curCol, Map& map, Animations& doorAnime);
	static const int brickSize = 90;
};