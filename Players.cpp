#include "Players.h"
#include "Map.h"
#include <math.h>
#include "Animations.h"
#include <set>

Players::Players()
{
	key = false;
	std::fill(canPushBox, canPushBox + 7, false);
	x = brickSize * 27 + 25;
	y = brickSize * 12 + 15;
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
	int curYDistance = returnPlayerY() - 6 * Map::brickSize;
	int curRow = curYDistance / Map::brickSize;
	return curRow;
}

int Players::calculateCurCol()
{
	int curXDistance = returnPlayerX() - 11 * Map::brickSize;
	int curCol = curXDistance / Map::brickSize;
	return curCol;
}

bool Players::checkOnDownCageCollision(bool canMoveDown)
{
	if (returnPlayerY() + offset >= brickSize * 11 + 25)
	{
		if ((returnPlayerX() >= brickSize * 31 - 30) && (returnPlayerX() <= brickSize * 31))
		{
			canMoveDown = false;
		}
	}
	return canMoveDown;
}

bool Players::checkOnMoveDown(Boxes& box, Animations& anime, Map& map)
{
	int curRow = calculateCurRow();
	int curCol = calculateCurCol();

	curCol += 11;
	curRow += 6;

	bool canMoveDown = true;

	checkOnKey(curRow, curCol, 0);
	checkOnDoor('D', map, anime);

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
		else if ((fabs((float)(box.getBoxX(i) - x)) <= 35) && (!canPushBox[i]) && (fabs((float)(box.getBoxY(i) - y)) <= 57) && (box.getBoxY(i) < y))
		{
			canMoveDown = false;
		}
	}

	if (anime.getCageAnimationState())
	{
		map.firstLevelMap[12][31] = ' ';
	}

	if (map.firstLevelMap[curRow + 1][curCol] != ' ')
	{
		if (map.firstLevelMap[curRow + 1][curCol] != 'T' && map.firstLevelMap[curRow + 1][curCol] != '.' && map.firstLevelMap[curRow + 1][curCol + 1] != 'G' && returnPlayerY() + 4 >= curRow * brickSize + 30)
		{
			canMoveDown = false;
		}
	}
	canMoveDown = checkOnDownCageCollision(canMoveDown);

	std::fill(canPushBox, canPushBox + 7, false);

	return canMoveDown;
}

bool Players::checkOnMoveUp(Boxes& box, Animations& anime, Map& map)
{
	int curRow = calculateCurRow();
	int curCol = calculateCurCol();

	curCol += 11;
	curRow += 6;

	bool canMoveUp = true;

	checkOnKey(curRow, curCol, 1);
	checkOnDoor('U', map, anime);

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

	if (((map.firstLevelMap[curRow - 1][curCol] != ' ') && (map.firstLevelMap[curRow - 1][curCol] != 'T') && (map.firstLevelMap[curRow - 1][curCol] != '.') && (map.firstLevelMap[curRow - 1][curCol] != 'G')) && (returnPlayerY() - 4 <= curRow * brickSize))
	{
		canMoveUp = false;
	}

	std::fill(canPushBox, canPushBox + 7, false);

	return canMoveUp;
}

bool Players::checkOnMoveLeft(Boxes& box, Animations& anime, Map& map)
{
	int curRow = calculateCurRow();
	int curCol = calculateCurCol();

	curCol += 11;
	curRow += 6;

	bool canMoveLeft = true;

	checkOnKey(curRow, curCol, 2);
	checkOnDoor('L', map, anime);

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

	if (((map.firstLevelMap[curRow][curCol - 1] != ' ') && (map.firstLevelMap[curRow][curCol - 1] != 'T') && (map.firstLevelMap[curRow][curCol - 1] != '.') && (map.firstLevelMap[curRow][curCol - 1] != 'G')) && (returnPlayerX() - 4 <= curCol * brickSize))
	{
		canMoveLeft = false;
	}
	std::fill(canPushBox, canPushBox + 7, false);

	return canMoveLeft;
}

bool Players::checkOnRightCageCollision(int curRow, int curCol, bool canMoveRight)
{
	if (returnPlayerY() >= brickSize * 12 - 55)
	{
		canMoveRight = false;
	}
	return canMoveRight;
}

bool Players::checkOnMoveRight(Boxes& box, Animations& anime, Map& map)
{
	int curRow = calculateCurRow();
	int curCol = calculateCurCol();

	curCol += 11;
	curRow += 6;

	bool canMoveRight = true;

	checkOnKey(curRow, curCol, 3);
	checkOnDoor('R', map, anime);

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

	if (anime.getCageAnimationState())
	{
		map.firstLevelMap[12][31] = ' ';
	}

	if (((map.firstLevelMap[curRow][curCol + 1] != ' ') && (map.firstLevelMap[curRow][curCol + 1] != 'T') && (map.firstLevelMap[curRow][curCol + 1] != '.') && (map.firstLevelMap[curRow][curCol + 1] != 'G')) && (returnPlayerX() + offset >= curCol * brickSize + 45))
	{
		canMoveRight = false;
	}

	if (((map.firstLevelMap[curRow][curCol + 1] == 'C') || (map.firstLevelMap[curRow + 1][curCol + 1] == 'C')) && (returnPlayerX() + offset >= curCol * brickSize + 45))
	{
		if (!anime.getCageAnimationState())
			canMoveRight = checkOnRightCageCollision(curRow, curCol, canMoveRight);
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
					if (fabs((float)(box.getBoxY(i) - box.getBoxY(indexOfBox))) <= 57)
					{
						if ((box.getBoxX(i) - box.getBoxX(indexOfBox) <= 61) && (box.getBoxX(i) - box.getBoxX(indexOfBox) >= 0))
							canPushBox[indexOfBox] = false;
					}
				}
				if (dir == 'L')
				{
					if (fabs((float)(box.getBoxY(i) - box.getBoxY(indexOfBox))) <= 57)
					{
						if ((box.getBoxX(indexOfBox) - box.getBoxX(i) <= 61) && (box.getBoxX(indexOfBox) - box.getBoxX(i) >= 0))
							canPushBox[indexOfBox] = false;
					}
				}
				if (dir == 'D')
				{
					if (fabs((float)(box.getBoxX(i) - box.getBoxX(indexOfBox))) <= 57)
					{
						if ((box.getBoxY(i) - box.getBoxY(indexOfBox) <= 61) && (box.getBoxY(i) - box.getBoxY(indexOfBox) >= 0))
							canPushBox[indexOfBox] = false;
					}
				}
				if (dir == 'U')
				{
					if (fabs((float)(box.getBoxX(i) - box.getBoxX(indexOfBox))) <= 57)
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
	else if ((dir == 'D') && (fabs((float)(box.getBoxY(indexOfBox) - y)) <= 57) && (fabs((float)(box.getBoxX(indexOfBox) - x)) <= 35))
	{
		float a = box.getBoxY(indexOfBox);
		canPushBox[indexOfBox] = true;
	}
	else
	{
		canPushBox[indexOfBox] = false;
	}

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

void Players::updateRight(Boxes& box, Animations& cage, Map& map)
{
	if (checkOnMoveRight(box, cage, map))
	{
		x += offset;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 96, 24, 32));
	}
}

void Players::updateDown(Boxes& box, Animations& cage, Map& map)
{
	if (checkOnMoveDown(box, cage, map))
	{
		y += offset;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 0, 24, 32));
	}
}

void Players::updateUp(Boxes& box, Animations& anime, Map& map)
{
	if (checkOnMoveUp(box, anime, map))
	{
		y -= offset;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 32, 24, 32));
	}
}

void Players::updateLeft(Boxes& box, Animations& anime, Map& map)
{
	if (checkOnMoveLeft(box, anime, map))
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
			x += 3;
			map.setPlateX(map.getPlateX() + 3);
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

void Players::move(sf::RenderWindow& window, Map& map, Animations& anime, Boxes& box, Animations& cage)
{
	if (!anime.getStay())
	{
		if (curImg > 6)
		{
			curImg = 0;
		}
		switch (dir)
		{
		case Direction::down:
		{
			updateDown(box, anime, map);
			break;
		}
		case Direction::up:
		{
			updateUp(box, anime, map);
			break;
		}
		case Direction::left:
		{
			updateLeft(box, anime, map);
			break;
		}
		case Direction::right:
		{
			updateRight(box, anime, map);
			break;
		}
		}
		sprite.setPosition(x, y);
	}
	if (checkOnTeleport(map) && (map.getPlateY() <= 7 * brickSize - 5))
	{
		anime.setStay(true);
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

void Players::checkOnBottomDoor(int curRow, int curCol, Map& map, Animations& doorAnime)
{
	if (map.firstLevelMap[curRow + 1][curCol] == 'D') 
	{
		if ((returnPlayerY() + offset >= (curRow + 1) * brickSize - 60) && isHasKey())
		{
			doorAnime.setDoorAnimationState(true);
		}
	}
}

void Players::checkOnTopDoor(int curRow, int curCol, Map& map, Animations& doorAnime)
{
	if (map.firstLevelMap[curRow - 1][curCol] == 'D')
	{
		if ((returnPlayerY() - offset <= curRow * brickSize) && isHasKey())
		{
			doorAnime.setDoorAnimationState(true);
		}
	}
}

void Players::checkOnLeftDoor(int curRow, int curCol, Map& map, Animations& doorAnime)
{
	if (map.firstLevelMap[curRow][curCol - 1] == 'D')
	{
		if ((returnPlayerX() - offset <= curCol * brickSize) && isHasKey())
		{
			doorAnime.setDoorAnimationState(true);
		}
	}
}

void Players::checkOnRightDoor(int curRow, int curCol, Map& map, Animations& doorAnime)
{
	if (map.firstLevelMap[curRow][curCol + 1] == 'D')
	{
		float a = returnPlayerX();
		if ((returnPlayerX() + offset >= (curCol + 1) * brickSize - 45) && isHasKey())
		{
			doorAnime.setDoorAnimationState(true);
		}
	}
}

void Players::checkOnDoor(char dir, Map& map, Animations& doorAnime)
{
	int curRow = calculateCurRow();
	int curCol = calculateCurCol();

	curCol += 11;
	curRow += 6;

	switch (dir)
	{
	case 'D':
	{
		checkOnBottomDoor(curRow, curCol, map, doorAnime);
		break;
	}
	case 'U':
	{
		checkOnTopDoor(curRow, curCol, map, doorAnime);
		break;
	}
	case 'L':
	{
		checkOnLeftDoor(curRow, curCol, map, doorAnime);
		break;
	}
	case 'R':
	{
		checkOnRightDoor(curRow, curCol, map, doorAnime);
		break;
	}
	}
}