#include "Animations.h"

Animations::Animations()
{
	cageImg.loadFromFile("Images/cage.png");
	cageTexture.loadFromImage(cageImg);
	cageSprite.setTexture(cageTexture);
	cageSprite.setTextureRect(sf::IntRect(0, 0, 90, 90));

	doorImg.loadFromFile("Images/doors.png");
	doorTexture.loadFromImage(doorImg);
	doorSprite.setTexture(doorTexture);
	doorSprite.setTextureRect(sf::IntRect(107, 7, 95, 95));

	leftDoorImg.loadFromFile("Images/doors.png");
	leftDoorTexture.loadFromImage(leftDoorImg);
	leftDoorSprite.setTexture(leftDoorTexture);
	leftDoorSprite.setTextureRect(sf::IntRect(154.5, 7, 47.5, 95));

	rightDoorImg.loadFromFile("Images/doors.png");
	rightDoorTexture.loadFromImage(rightDoorImg);
	rightDoorSprite.setTexture(rightDoorTexture);
	rightDoorSprite.setTextureRect(sf::IntRect(202, 7, 47.5, 95));

	initializeDoors();
}

void Animations::initializeDoors()
{
	for (int i = 0; i < Map::mapHeight; i++)
	{
		for (int j = 0; j < Map::mapWidth; j++)
		{
			if (map.firstLevelMap[i][j] == 'D')
			{
				numOfDoors++;
				position = sf::Vector2f(j, i);
				doors.push_back(position);
				isCanStartDoorAnimation.push_back(false);
				door.push_back(DoorsProperties(205.0, 46.5, 40.5, 0.0, 47.5));
			}
		}
	}
}

void Animations::resetMap(Map& map, Animations& anime)
{
	isCanStartDoorAnimation.clear();
	door.clear();
	int x, y;
	for (int i = 0; i < numOfDoors; i++)
	{
		x = doors[i].x;
		y = doors[i].y;
		map.firstLevelMap[y][x] = 'D';
		isCanStartDoorAnimation.push_back(false);
		door.push_back(DoorsProperties(205.0, 46.5, 40.5, 0.0, 47.5));
	}
}

void Animations::setCagePos(sf::RenderWindow& window, Boxes& box, Map& map, sf::Clock& cageClock, SoundManager& sound, Animations& anime)
{
	int cageX = 8;
	int cageY = 31;
	if (anime.isCageAnimationStarted)
	{
		map.firstLevelMap[cageX][cageY] = ' ';
	}
	else
	{
		cageSprite.setPosition(brickSize * 31, brickSize * 8);
		window.draw(cageSprite);
		startCageAnimation(box, map, window, cageClock, sound, anime);
	}
}

void Animations::startCageAnimation(Boxes& box, Map& map, sf::RenderWindow& window, sf::Clock& cageClock, SoundManager& sound, Animations& anime)
{
	#define numOfActivePoints 6
	int countOfPoints = 0;
	for (int i = 0; i < Map::mapHeight; i++)
	{
		for (int j = 0; j < Map::mapWidth; j++)
		{
			if (map.firstLevelMap[i][j] == 'G')
				countOfPoints++;
		}
	}
	if (countOfPoints == numOfActivePoints)
	{
		if (sound.openCage.getStatus() != sf::Sound::Playing)
			sound.playOpeningOfCage();
		sf::Time curTime = cageClock.getElapsedTime();
		if (curTime.asSeconds() >= 0.01) 
		{
			setCageHeight(getCageHeight() - 1);
			cageSprite.setTextureRect(sf::IntRect(0, 0, 90, getCageHeight()));
			window.draw(cageSprite);
			if (getCageHeight() == 0)
				anime.isCageAnimationStarted = true;
			cageClock.restart();
		}
	}
	else
	{
		const int startCageHeight = 90;
		setCageHeight(startCageHeight);
		cageSprite.setTextureRect(sf::IntRect(0, 0, 90, getCageHeight()));
		window.draw(cageSprite);
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

void Animations::checkOnOpenDoor(Map& map, sf::RenderWindow& window, sf::Clock& leftDoorClock, sf::Clock& rightDoorClock)
{
	for (int i = 0; i < numOfDoors; i++)
	{
		if (getDoorAnimationState(i))
		{
			startDoorAnimation(i, map, window, leftDoorClock, rightDoorClock);
		}
	}
}

void Animations::startDoorAnimation(int numOfDoor, Map& map, sf::RenderWindow& window, sf::Clock& leftDoorClock, sf::Clock& rightDoorClock)
{
	int curDoorCol = doors[numOfDoor].x;
	int curDoorRow = doors[numOfDoor].y;
	map.firstLevelMap[curDoorRow][curDoorCol] = 'C';
	if ((leftDoorClock.getElapsedTime().asMilliseconds() > 85) && (door[numOfDoor].leftDoorStartX < 252.0) && (door[numOfDoor].leftDoorWidth > 0))
	{
		door[numOfDoor].leftDoorOffset--;
		door[numOfDoor].leftDoorWidth -= 1;
		door[numOfDoor].leftDoorStartX++;
		leftDoorClock.restart();
	}
	if ((rightDoorClock.getElapsedTime().asMilliseconds() > 100) && (door[numOfDoor].rightDoorOffset < 95) && (door[numOfDoor].rightDoorWidth > 0))
	{
		door[numOfDoor].rightDoorOffset++;
		door[numOfDoor].rightDoorWidth -= 1;
		rightDoorClock.restart();
	}
	if (door[numOfDoor].leftDoorWidth <= 0)
	{
		map.firstLevelMap[curDoorRow][curDoorCol] = ' ';
	}
	leftDoorSprite.setTextureRect(sf::IntRect(door[numOfDoor].leftDoorStartX, 7, door[numOfDoor].leftDoorWidth, 95));
	leftDoorSprite.setPosition(brickSize * curDoorCol, brickSize * curDoorRow);
	window.draw(leftDoorSprite);
	rightDoorSprite.setTextureRect(sf::IntRect(250.0, 7, door[numOfDoor].rightDoorWidth, 95));
	rightDoorSprite.setPosition(brickSize * curDoorCol + door[numOfDoor].rightDoorOffset, brickSize * curDoorRow);
	window.draw(rightDoorSprite);
}