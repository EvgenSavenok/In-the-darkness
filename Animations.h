#pragma once
#include <SFML/Graphics.hpp>
#include "Boxes.h"
#include "Map.h"
#include "SoundManager.h"

class Animations
{
private:
	bool isStayOnTeleport = false;
	float interval = 1.5;
	bool isFirstCycle = false;
	bool isFirstSetTeleport = true;

	sf::Image cageImg;
	sf::Texture cageTexture;
	sf::Sprite cageSprite;

	sf::Image doorImg;
	sf::Texture doorTexture;
	sf::Sprite doorSprite;

	sf::Image leftDoorImg;
	sf::Texture leftDoorTexture;
	sf::Sprite leftDoorSprite;

	sf::Image rightDoorImg;
	sf::Texture rightDoorTexture;
	sf::Sprite rightDoorSprite;

	bool isCanStartBoxAnime = false;
	float cageHeight = 90;

	bool isCageAnimationStarted = false;

	float brickSize = 90;

	void startDoorAnimation(int numOfDoor, Map& map, sf::RenderWindow& window, sf::Clock& leftDoorClock, sf::Clock& rightDoorClock);
	void initializeDoors();

	Map map;
	
public:
	sf::Sprite getCageSprite() { return cageSprite; };
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
	void setCagePos(sf::RenderWindow& window, Boxes& box, Map& map, sf::Clock& cageClock, SoundManager& sound, Animations& anime);
	void startCageAnimation(Boxes& box, Map& map, sf::RenderWindow& window, sf::Clock& cageClock, SoundManager& sound, Animations& anime);
	void checkOnOpenDoor(Map& map, sf::RenderWindow& window, sf::Clock& leftDoorClock, sf::Clock& rightDoorClock);
	int checkCurDoorNum(int curRow, int curCol);
	int numOfDoors = 0;
	std::vector<sf::Vector2f> doors;
	struct DoorsProperties {
		float leftDoorStartX = 205;
		float leftDoorWidth = 46.5;
		float rightDoorWidth = 40.5;
		float leftDoorOffset = 0;
		float rightDoorOffset = 47.5;
		DoorsProperties(float leftDoorStartX, float leftDoorWidth, float rightDoorWidth, float leftDoorOffset, float rightDoorOffset)
		{
			this->leftDoorStartX = leftDoorStartX;
			this->leftDoorWidth = leftDoorWidth;
			this->rightDoorWidth = rightDoorWidth;
			this->leftDoorOffset = leftDoorOffset;
			this->rightDoorOffset = rightDoorOffset;
		}
	};
	std::vector<DoorsProperties> door;
	std::vector<bool> isCanStartDoorAnimation;
	sf::Vector2f position;
	void resetMap(Map& map, Animations& anime);
};