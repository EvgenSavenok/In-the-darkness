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

	float brickSize = 90;

public:
	bool getStay() { return isStayOnTeleport; }
	void setStay(bool isStayOnTeleport) { this->isStayOnTeleport = isStayOnTeleport; }

	float getInterval() { return interval; }
	void setInterval(float interval) { this->interval = interval; }
	bool getFirstCycleInfo() { return isFirstCycle; }
	void setFirstCycleInfo(bool isFirstCycle) { this->isFirstCycle = isFirstCycle; }
	bool getFirstSetInfo() { return isFirstSetTeleport; }
	void setFirstSetInfo(bool isFirstSetTeleport) { this->isFirstSetTeleport = isFirstSetTeleport; }
	Animations();
	void setCagePos(sf::RenderWindow& window, Boxes& box, Map& map);
	void startCageAnimation(Boxes& box, Map& map);
};