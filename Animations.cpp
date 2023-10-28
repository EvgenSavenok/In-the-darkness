#include "Animations.h"
#include "Map.h"

Animations::Animations()
{
	cageImg.loadFromFile("Images/cage.png");
	cageTexture.loadFromImage(cageImg);
	cageSprite.setTexture(cageTexture);
	cageSprite.setTextureRect(sf::IntRect(0, 0, 90, 90));
	initializeDoors();
}

void Animations::initializeDoors()
{
	Map map;
	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 43; j++)
		{
			if (map.firstLevelMap[i][j] == 'D')
			{
				numOfDoors++;
				position = sf::Vector2f(j, i);
				doors.push_back(position);
				isCanStartDoorAnimation.push_back(false);
			}
		}
	}
}

void Animations::setCagePos(sf::RenderWindow& window, Boxes& box, Map& map, sf::Clock& cageClock)
{
	if (getCageAnimationState())
	{
		map.firstLevelMap[12][31] = ' ';
	}
	else
	{
		cageSprite.setPosition(brickSize * 31, brickSize * 12);
		window.draw(cageSprite);
		startCageAnimation(box, map, window, cageClock);
	}
}

void Animations::startCageAnimation(Boxes& box, Map& map, sf::RenderWindow& window, sf::Clock& cageClock)
{
	#define numOfActivePoints 1
	int countOfPoints = 0;
	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 43; j++)
		{
			if (map.firstLevelMap[i][j] == 'G')
				countOfPoints++;
		}
	}
	if (countOfPoints == numOfActivePoints)
	{
		sf::Time curTime = cageClock.getElapsedTime();
		if (curTime.asSeconds() >= 0.01) 
		{
			setCageHeight(getCageHeight() - 1);
			cageSprite.setTextureRect(sf::IntRect(0, 0, 90, getCageHeight()));
			window.draw(cageSprite);
			if (getCageHeight() == 0)
				setCageAnimationState(true);
			cageClock.restart();
		}
	}
}

int Animations::checkCurDoorNum(int curRow, int curCol)
{
	for (int i = 0; i < numOfDoors; i++)
	{
		if ((curCol == doors[i].x) && (curRow == doors[i].y))
		{
			return i;
		}
	}
}

void Animations::checkOnOpenDoor(Map& map)
{
	for (int i = 0; i < numOfDoors; i++)
	{
		if (getDoorAnimationState(i))
		{
			startDoorAnimation(i, map);
		}
	}
}

void Animations::startDoorAnimation(int numOfDoor, Map& map)
{
	int curDoorCol = doors[numOfDoor].x;
	int curDoorRow = doors[numOfDoor].y;
	map.firstLevelMap[curDoorCol][curDoorRow] == ' ';
}