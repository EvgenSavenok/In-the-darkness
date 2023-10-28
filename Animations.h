#pragma once
#include <SFML/Graphics.hpp>
#include "Boxes.h"
#include "Map.h"

class Animations
{
private:
	bool isStayOnTeleport = false;
	float interval = 3;
	bool isFirstCycle = false;
	bool isFirstSetTeleport = true;

	sf::Image cageImg;
	sf::Texture cageTexture;
	sf::Sprite cageSprite;

	bool isCanStartBoxAnime = false;
	float cageHeight = 90;

	bool isCageAnimationStarted = false;

	float brickSize = 90;

	void startDoorAnimation(int numOfDoor, Map& map);
	sf::Vector2f position;
	void initializeDoors();
	int numOfDoors = 0;
	std::vector<bool> isCanStartDoorAnimation;
	
public:
	bool getStay() { return isStayOnTeleport; }
	void setStay(bool isStayOnTeleport) { this->isStayOnTeleport = isStayOnTeleport; }
	float getCageHeight() { return cageHeight; }
	void setCageHeight(float cageHeight) { this->cageHeight = cageHeight; }
	void setCageAnimationState(bool isCageAnimationStarted) { this->isCageAnimationStarted = isCageAnimationStarted; }
	bool getCageAnimationState() { return isCageAnimationStarted; }
	void setDoorAnimationState(bool isCanStartDoorAnimation, int numOfDoor) { this->isCanStartDoorAnimation[numOfDoor] = isCanStartDoorAnimation; }
	bool getDoorAnimationState(int numOfDoor) { return isCanStartDoorAnimation[numOfDoor]; }

	float getInterval() { return interval; }
	void setInterval(float interval) { this->interval = interval; }
	bool getFirstCycleInfo() { return isFirstCycle; }
	void setFirstCycleInfo(bool isFirstCycle) { this->isFirstCycle = isFirstCycle; }
	bool getFirstSetInfo() { return isFirstSetTeleport; }
	void setFirstSetInfo(bool isFirstSetTeleport) { this->isFirstSetTeleport = isFirstSetTeleport; }
	Animations();
	void setCagePos(sf::RenderWindow& window, Boxes& box, Map& map, sf::Clock& cageClock);
	void startCageAnimation(Boxes& box, Map& map, sf::RenderWindow& window, sf::Clock& cageClock);
	void checkOnOpenDoor(Map& map);
	int checkCurDoorNum(int curRow, int curCol);
	std::vector<sf::Vector2f> doors;
};