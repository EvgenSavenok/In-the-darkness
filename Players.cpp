#include "Players.h"
#include "Map.h"
#include <math.h>
#include "Animations.h"

Players::Players()
{
	key = false;
	std::fill(canPushBox, canPushBox + 7, false);
	x = brickSize * 26 + 25;
	y = brickSize * 7 + 15;
	curImg = 0;
	dir = Direction::down;
	img.loadFromFile("Images/player.png");
	texture.loadFromImage(img);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 24, 32));
	sprite.setPosition(x, y);
	sprite.setScale(1.9, 1.9);

	keyX = brickSize * 31 + 30;
	keyY = brickSize * 12 + 30;
	keySprite.setPosition(keyX, keyY);

	keyImg.loadFromFile("Images/card-key.png");
	keyTexture.loadFromImage(keyImg);
	keySprite.setTexture(keyTexture);
	keySprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
}

void Players::drawKey(sf::RenderWindow& window)
{
	keyX = brickSize * 31 + 30;
	keyY = brickSize * 12 + 30;
	keySprite.setPosition(keyX, keyY);

	if (!isHasKey())
	{
		window.draw(keySprite);
	}
}

void Players::checkOnKey(int curRow, int curCol, int curDir)
{
	int curXDistance = returnKeyX() - 11 * brickSize;
	int curKeyCol = curXDistance / brickSize;

	int curYDistance = returnKeyY() + 50 - 6 * brickSize;
	int curKeyRow = curYDistance / brickSize;

	curKeyCol += 11;
	curKeyRow += 6;

	if ((curDir == 0) && (fabs((float)(keyY - y)) <= 20) && (fabs((float)(keyX - x)) <= 10))
	{
		key = true;
	}
	if ((curDir == 1) && (fabs((float)(keyY - y)) <= 20) && (fabs((float)(keyX - x)) <= 10))
	{
		key = true;
	}
	if ((curDir == 2) && (fabs((float)(keyX - x)) <= 20) && (fabs((float)(keyY - y)) <= 20))
	{
		key = true;
	}
	if ((curDir == 3) && (fabs((float)(keyX - x)) <= 20) && (fabs((float)(keyY - y)) <= 20))
	{
		key = true;
	}
}

int Players::calculateCurRow()
{
	int curYDistance = returnY() - 6 * Map::brickSize;
	int curRow = curYDistance / Map::brickSize;
	return curRow;
}

int Players::calculateCurCol()
{
	int curXDistance = returnX() - 11 * Map::brickSize;
	int curCol = curXDistance / Map::brickSize;
	return curCol;
}

bool Players::checkOnMoveDown(Boxes& box)
{
	Map map;

	int curRow = calculateCurRow();
	int curCol = calculateCurCol();

	curCol += 11;
	curRow += 6;

	bool canMoveDown = true;

	checkOnKey(curRow, curCol, 0);
	for (int i = 0; i < 7; i++)
	{
		checkOnBox(curRow, curCol, 'D', box, map, i);
		checkOnNearBox(curRow, curCol, 'D', box, map, i);
		if (canPushBox[i])
		{
			box.pushBox(curRow, curCol, 'D', box, i);
		}
		if ((fabs((float)(box.getBoxX(i) - x)) <= 35) && (!canPushBox[i]) && (fabs((float)(box.getBoxY(i) - y)) <= 64) && (box.getBoxY(i) > y))
		{
			canMoveDown = false;
		}
		else if ((fabs((float)(box.getBoxX(i) - x)) <= 35) && (!canPushBox[i]) && (fabs((float)(box.getBoxY(i) - y)) <= 59) && (box.getBoxY(i) < y))
		{
			canMoveDown = false;
		}
	}

	if ((((map.firstLevelMap[curRow + 1][curCol] != ' ') && (map.firstLevelMap[curRow + 1][curCol] != 'T' && (map.firstLevelMap[curRow + 1][curCol] != '.')) && (map.firstLevelMap[curRow + 1][curCol + 1] != 'G')) && (returnY() + 4 >= curRow * brickSize + 25)))
	{
		canMoveDown = false;
	}

	std::fill(canPushBox, canPushBox + 7, false);

	return canMoveDown;
}

bool Players::checkOnMoveUp(Boxes& box)
{
	Map map;

	int curRow = calculateCurRow();
	int curCol = calculateCurCol();

	curCol += 11;
	curRow += 6;

	bool canMoveUp = true;

	checkOnKey(curRow, curCol, 1);
	for (int i = 0; i < 7; i++)
	{
		checkOnBox(curRow, curCol, 'U', box, map, i);
		checkOnNearBox(curRow, curCol, 'U', box, map, i);
		if (canPushBox[i])
		{
			box.pushBox(curRow, curCol, 'U', box, i);
		}
		if ((fabs((float)(box.getBoxX(i) - x)) <= 40) && (!canPushBox[i]) && (fabs((float)(box.getBoxY(i) - y)) <= 60))
		{
			canMoveUp = false;
		}
	}

	if (((map.firstLevelMap[curRow - 1][curCol] != ' ') && (map.firstLevelMap[curRow - 1][curCol] != 'T') && (map.firstLevelMap[curRow - 1][curCol] != '.') && (map.firstLevelMap[curRow - 1][curCol] != 'G')) && (returnY() - 4 <= curRow * brickSize))
	{
		canMoveUp = false;
	}

	std::fill(canPushBox, canPushBox + 7, false);

	return canMoveUp;
}

bool Players::checkOnMoveLeft(Boxes& box)
{
	Map map;

	int curRow = calculateCurRow();
	int curCol = calculateCurCol();

	curCol += 11;
	curRow += 6;

	bool canMoveLeft = true;

	checkOnKey(curRow, curCol, 2);
	for (int i = 0; i < 7; i++)
	{
		checkOnBox(curRow, curCol, 'L', box, map, i);
		checkOnNearBox(curRow, curCol, 'L', box, map, i);
		if (canPushBox[i])
		{
			box.pushBox(curRow, curCol, 'L', box, i);
		}
		if (x < box.getBoxX(i))
		{
			if ((fabs((float)(box.getBoxX(i) - x)) <= 30) && (!canPushBox[i]) && (fabs((float)(box.getBoxY(i) - y)) <= 55))
			{
				canMoveLeft = false;
			}
		}
		else
		{
			if ((fabs((float)(box.getBoxX(i) - x)) <= 55) && (!canPushBox[i]) && (fabs((float)(box.getBoxY(i) - y)) <= 55))
			{
				canMoveLeft = false;
			}
		}
	}

	if (((map.firstLevelMap[curRow][curCol - 1] != ' ') && (map.firstLevelMap[curRow][curCol - 1] != 'T') && (map.firstLevelMap[curRow][curCol - 1] != '.') && (map.firstLevelMap[curRow][curCol - 1] != 'G')) && (returnX() - 4 <= curCol * brickSize))
	{
		canMoveLeft = false;
	}
	std::fill(canPushBox, canPushBox + 7, false);

	return canMoveLeft;
}

bool Players::checkOnMoveRight(Boxes& box)
{
	Map map;

	int curRow = calculateCurRow();
	int curCol = calculateCurCol();

	curCol += 11;
	curRow += 6;

	bool canMoveRight = true;

	checkOnKey(curRow, curCol, 3);
	for (int i = 0; i < 7; i++)
	{
		checkOnBox(curRow, curCol, 'R', box, map, i);
		checkOnNearBox(curRow, curCol, 'R', box, map, i);
		if (canPushBox[i])
		{
			box.pushBox(curRow, curCol, 'R', box, i);
		}
		if (((fabs((float)(box.boxes[i].x - x)) <= 40) && (!canPushBox[i])) && (fabs((float)(box.boxes[i].y - y)) <= 50))
		{
			canMoveRight = false;
		}
	}

	if ((((map.firstLevelMap[curRow][curCol + 1] != ' ') && (map.firstLevelMap[curRow][curCol + 1] != 'T') && (map.firstLevelMap[curRow][curCol + 1] != '.') && (map.firstLevelMap[curRow][curCol + 1] != 'G')) && (returnX() + offset >= curCol * brickSize + 45)))
	{
		canMoveRight = false;
	}

	std::fill(canPushBox, canPushBox + 7, false);

	return canMoveRight;
}

void Players::checkOnNearBox(int curRow, int curCol, char dir, Boxes& box, Map& map, int indexOfBox)
{
	if (canPushBox[indexOfBox])
	{
		for (int i = 0; i < 7; i++)
		{
			if (i != indexOfBox)
			{
				if (dir == 'R')
				{
					if (fabs((float)(box.getBoxY(i) - box.getBoxY(indexOfBox))) <= 60)
					{
						if ((box.getBoxX(i) - box.getBoxX(indexOfBox) <= 61) && (box.getBoxX(i) - box.getBoxX(indexOfBox) >= 0))
							canPushBox[indexOfBox] = false;
					}
				}
				if (dir == 'L')
				{
					if (fabs((float)(box.getBoxY(i) - box.getBoxY(indexOfBox))) <= 60)
					{
						if ((box.getBoxX(indexOfBox) - box.getBoxX(i) <= 61) && (box.getBoxX(indexOfBox) - box.getBoxX(i) >= 0))
							canPushBox[indexOfBox] = false;
					}
				}
				if (dir == 'D')
				{
					if (fabs((float)(box.getBoxX(i) - box.getBoxX(indexOfBox))) <= 60)
					{
						if ((box.getBoxY(i) - box.getBoxY(indexOfBox) <= 61) && (box.getBoxY(i) - box.getBoxY(indexOfBox) >= 0))
							canPushBox[indexOfBox] = false;
					}
				}
				if (dir == 'U')
				{
					if (fabs((float)(box.getBoxX(i) - box.getBoxX(indexOfBox))) <= 60)
					{
						if ((box.getBoxY(indexOfBox) - box.getBoxY(i) <= 61) && (box.getBoxY(indexOfBox) - box.getBoxY(i) >= 0))
							canPushBox[indexOfBox] = false;
					}
				}
			}
		}
	}
}

void Players::checkOnBox(int curRow, int curCol, char dir, Boxes& box, Map& map, int indexOfBox)
{
	int curXDistance = box.getBoxX(indexOfBox) - 11 * brickSize;
	int curBoxCol = curXDistance / brickSize;

	int curYDistance = box.getBoxY(indexOfBox) + 50 - 6 * brickSize;
	int curBoxRow = curYDistance / brickSize;

	curBoxCol += 11;
	curBoxRow += 6;

	if ((dir == 'R') && (fabs((float)(box.getBoxY(indexOfBox) - y)) <= 45) && (fabs((float)(box.getBoxX(indexOfBox) - x)) <= 45))
	{
		canPushBox[indexOfBox] = true;
	}
	else if ((box.getBoxX(indexOfBox) > x) && (dir == 'L') && (fabs((float)(box.getBoxY(indexOfBox) - y)) <= 45) && (fabs((float)(box.getBoxX(indexOfBox) - x)) <= 30))
	{
		canPushBox[indexOfBox] = true;
	}
	else if ((box.getBoxX(indexOfBox) < x) && (dir == 'L') && (fabs((float)(box.getBoxY(indexOfBox) - y)) <= 45) && (fabs((float)(box.getBoxX(indexOfBox) - x)) <= 55))
	{
		canPushBox[indexOfBox] = true;
	}
	else if ((dir == 'U') && (fabs((float)(box.getBoxY(indexOfBox) - y)) <= 60) && (fabs((float)(box.getBoxX(indexOfBox) - x)) <= 40))
	{
		canPushBox[indexOfBox] = true;
	}
	else if ((dir == 'D') && (fabs((float)(box.getBoxY(indexOfBox) - y)) <= 64) && (fabs((float)(box.getBoxX(indexOfBox) - x)) <= 35) && (box.getBoxY(indexOfBox) > y))
	{
		canPushBox[indexOfBox] = true;
	}
	else if ((dir == 'D') && (fabs((float)(box.getBoxY(indexOfBox) - y)) <= 59) && (fabs((float)(box.getBoxX(indexOfBox) - x)) <= 35) && (box.getBoxY(indexOfBox) < y))
	{
		canPushBox[indexOfBox] = true;
	}
	else
	{
		canPushBox[indexOfBox] = false;
	}

	//Check on box collision

	if ((map.firstLevelMap[curBoxRow][curBoxCol + 1] != ' ') && (dir == 'R') && (map.firstLevelMap[curBoxRow][curBoxCol + 1] != '.') && (map.firstLevelMap[curBoxRow][curBoxCol + 1] != 'G'))
	{
		if (box.getBoxX(indexOfBox) + 66 > (curBoxCol + 1) * brickSize)
		{
			canPushBox[indexOfBox] = false;
		}
	}

	if ((map.firstLevelMap[curBoxRow][curBoxCol - 1] != ' ') && (dir == 'L') && (map.firstLevelMap[curBoxRow][curBoxCol - 1] != '.') && (map.firstLevelMap[curBoxRow][curBoxCol - 1] != 'G'))
	{
		if (box.getBoxX(indexOfBox) - 10 < curBoxCol * brickSize)
		{
			canPushBox[indexOfBox] = false;
		}
	}

	if ((map.firstLevelMap[curBoxRow - 1][curBoxCol] != ' ') && (dir == 'U') && (map.firstLevelMap[curBoxRow - 1][curBoxCol] != '.') && (map.firstLevelMap[curBoxRow - 1][curBoxCol] != 'G'))
	{
		if ((box.getBoxY(indexOfBox) - 7 < curBoxRow * brickSize))
		{
			canPushBox[indexOfBox] = false;
		}
	}

	if ((map.firstLevelMap[curBoxRow + 1][curBoxCol] != ' ') && (dir == 'D') && (map.firstLevelMap[curBoxRow + 1][curBoxCol] != '.') && (map.firstLevelMap[curBoxRow + 1][curBoxCol] != 'G'))
	{
		if (box.getBoxY(indexOfBox) - 25 > curBoxRow * brickSize)
		{
			canPushBox[indexOfBox] = false;
		}
	}
}

bool Players::checkOnTeleport(Map& map)
{
	int curRow = calculateCurRow();
	int curCol = calculateCurCol();

	curCol += 11;
	curRow += 6;

	if (map.firstLevelMap[curRow][curCol] == 'T')
	{
		return true;
	}
	return false;
}

void Players::updateRight(Boxes& box)
{
	if (checkOnMoveRight(box))
	{
		x += offset;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 96, 24, 32));
	}
}

void Players::updateDown(Boxes& box)
{
	if (checkOnMoveDown(box))
	{
		y += offset;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 0, 24, 32));
	}
}

void Players::updateUp(Boxes& box)
{
	if (checkOnMoveUp(box))
	{
		y -= offset;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 32, 24, 32));
	}
}

void Players::updateLeft(Boxes& box)
{
	if (checkOnMoveLeft(box))
	{
		x -= offset;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 64, 24, 32));
	}
}

bool Players::startTeleportAnimation(Map& map, sf::Clock teleportClock, Animations& animeOfTeleport)
{
	sf::Time curTime = teleportClock.getElapsedTime();
	float timing = curTime.asSeconds();
	if (timing >= animeOfTeleport.getInterval())
	{
		int curRow = calculateCurRow();
		int curCol = calculateCurCol();

		curCol += 11;
		curRow += 6;

		if (!animeOfTeleport.getFirstCycleInfo())
		{
			map.firstLevelMap[curRow][curCol] = 'B';
		}

		if ((map.getPlateX() < map.startXCoordinate + brickSize * 3) && (curTime.asSeconds() >= animeOfTeleport.getInterval()))
		{
			map.teleportSprite.setPosition(map.getPlateX() - brickSize, map.getPlateY());
			x += 30;
			map.setPlateX(map.getPlateX() + 30);
			if (animeOfTeleport.getFirstCycleInfo())
			{
				animeOfTeleport.setInterval(0.1);
			}
			animeOfTeleport.setFirstCycleInfo(true);
		}
		if ((map.getPlateX() >= map.startXCoordinate + brickSize * 3) && (map.getPlateY() > map.startYCoordinate - brickSize * 4 - 3) && (curTime.asSeconds() >= animeOfTeleport.getInterval()))
		{
			map.teleportSprite.setPosition(map.getPlateX() - brickSize, map.getPlateY());
			y -= 3;
			map.setPlateY(map.getPlateY() - 3);
		}
		if ((map.getPlateY() <= 7 * brickSize - 2) && (curCol == 16))
		{
			map.firstLevelMap[curRow][curCol] = 'T';
			animeOfTeleport.setStay(false);
		}
		return true;
	}
	return false;
}

void Players::move(sf::RenderWindow& window, Map& map, Animations& animeOfTeleport, Boxes& box)
{
	if (!animeOfTeleport.getStay())
	{
		if (curImg > 6)
		{
			curImg = 0;
		}
		switch (dir)
		{
		case Direction::down:
		{
			updateDown(box);
			break;
		}
		case Direction::up:
		{
			updateUp(box);
			break;
		}
		case Direction::left:
		{
			updateLeft(box);
			break;
		}
		case Direction::right:
		{
			updateRight(box);
			break;
		}
		}
		sprite.setPosition(x, y);
	}
	if (checkOnTeleport(map) && (map.getPlateY() <= 7 * brickSize - 5))
	{
		animeOfTeleport.setStay(true);
	}
}

bool Players::prepareForTeleportAnime(Animations& animeOfTeleport, Map& map, sf::Clock teleportClock, bool isNewCycle)
{
	if (animeOfTeleport.getStay())
	{
		int curRow = calculateCurRow();
		int curCol = calculateCurCol();

		curCol += 11;
		curRow += 6;

		if (animeOfTeleport.getFirstSetInfo())
		{
			map.startXCoordinate = brickSize * (curCol + 1);
			map.startYCoordinate = brickSize * curRow;
		}

		if (animeOfTeleport.getFirstSetInfo())
		{
			map.setPlateX(map.startXCoordinate);
			map.setPlateY(map.startYCoordinate);
			animeOfTeleport.setFirstSetInfo(false);
		}
		if (startTeleportAnimation(map, teleportClock, animeOfTeleport))
		{
			isNewCycle = true;
		}
		sprite.setPosition(x, y);
	}
	return isNewCycle;
}

bool Players::update(sf::Clock clock, Map& map, sf::Clock teleportClock, Animations& animeOfTeleport)
{
	bool isNewCycle = false;
	sf::Time curTime = clock.getElapsedTime();
	if (curTime.asSeconds() >= delayInSeconds)
	{
		curImg = 0;
		switch (dir)
		{
		case Direction::down:
		{
			sprite.setTextureRect(sf::IntRect(0, 0, 24, 32));
			break;
		}
		case Direction::up:
		{
			sprite.setTextureRect(sf::IntRect(0, 32, 24, 32));
			break;
		}
		case Direction::left:
		{
			sprite.setTextureRect(sf::IntRect(0, 64, 24, 32));
			break;
		}
		case Direction::right:
		{
			sprite.setTextureRect(sf::IntRect(0, 96, 24, 32));
			break;
		}
		}
	}
	isNewCycle = prepareForTeleportAnime(animeOfTeleport, map, teleportClock, isNewCycle);
	return isNewCycle;
}