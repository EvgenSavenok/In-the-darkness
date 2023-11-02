#include "Players.h"
#include "Map.h"
#include <math.h>
#include "Animations.h"

Player::Player()
{
	key = false;
	std::fill(canPushBox, canPushBox + 7, false);
	playerX = brickSize * 27 + 25;
	playerY = brickSize * 14 + 15;
	curImg = 0;
	playerDir = Direction::down;
	playerImg.loadFromFile("Images/player.png");
	texture.loadFromImage(playerImg);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 24, 32));
	sprite.setPosition(playerX, playerY);
	sprite.setScale(1.9, 1.9);

	keyX = brickSize * 31 + 30;
	keyY = brickSize * 12 + 30;
	keySprite.setPosition(keyX, keyY);

	keyImg.loadFromFile("Images/card-key.png");
	keyTexture.loadFromImage(keyImg);
	keySprite.setTexture(keyTexture);
	keySprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
}

void Player::drawKey(sf::RenderWindow& window)
{
	const int curKeyX = 31;
	const int curKeyY = 12;
	const int keyOffset = 30;
	keyX = brickSize * curKeyX + keyOffset;
	keyY = brickSize * curKeyY + keyOffset;
	keySprite.setPosition(keyX, keyY);

	if (!isHasKey())
	{
		window.draw(keySprite);
	}
	
}

void Player::checkOnKey(int curRow, int curCol, char curDir)
{
	int curXDistance = returnKeyX() - 11 * brickSize;
	int curKeyCol = curXDistance / brickSize + 11;

	int curYDistance = returnKeyY() + 50 - 6 * brickSize;
	int curKeyRow = curYDistance / brickSize + 6;

	const int keyYOffset = 20;
	const int keyXOffset = 10;

	if (curDir == 'D')
	{
		if ((fabs((float)(keyY - playerY)) <= keyYOffset) && (fabs((float)(keyX - playerX)) <= keyXOffset))
		{
			key = true;
		}
	}
	if (curDir == 'U') 
	{
		if ((fabs((float)(keyY - playerY)) <= keyYOffset) && (fabs((float)(keyX - playerX)) <= keyXOffset))
		{
			key = true;
		}
	}
	if (curDir == 'L')
	{
		if ((fabs((float)(keyX - playerX)) <= keyYOffset) && (fabs((float)(keyY - playerY)) <= keyYOffset))
		{
			key = true;
		}
	}	
	if (curDir == 'R')
	{
		if ((fabs((float)(keyX - playerX)) <= keyYOffset) && (fabs((float)(keyY - playerY)) <= keyYOffset))
		{
			key = true;
		}
	}
}

int Player::calculateCurPlayerRow()
{
	int curYDistance = returnPlayerY() - 6 * Map::brickSize;
	int curRow = curYDistance / Map::brickSize;
	return curRow;
}

int Player::calculateCurPlayerCol()
{
	int curXDistance = returnPlayerX() - 11 * Map::brickSize;
	int curCol = curXDistance / Map::brickSize;
	return curCol;
}

bool Player::checkOnDownCageCollision(bool canMoveDown)
{
	const int cageX = 31;
	const int cageY = 11;
	const int cageXOffset = 30;
	const int cageYOffset = 25;
	if (returnPlayerY() + offset >= brickSize * cageY + cageYOffset)
	{
		if ((returnPlayerX() >= brickSize * cageX - cageXOffset) && (returnPlayerX() <= brickSize * cageX))
		{
			canMoveDown = false;
		}
	}
	return canMoveDown;
}

bool Player::checkOnDownBoxCollisions(int curRow, int curCol, Boxes& box, Map& map)
{
	const int numOfPointsBoxes = 7;
	for (int i = 0; i < numOfPointsBoxes; i++)
	{
		checkOnBox(curRow, curCol, 'D', box, map, i);
		checkOnNearBox(curRow, curCol, 'D', box, map, i);
		if (canPushBox[i])
		{
			box.pushBox(curRow, curCol, 'D', box, i);
		}
		if ((fabs((float)(box.getBoxX(i) - playerX)) <= 35) && (!canPushBox[i]) && (fabs((float)(box.getBoxY(i) - playerY)) <= 64) && (box.getBoxY(i) > playerY))
		{
			return false;
		}
		else if ((fabs((float)(box.getBoxX(i) - playerX)) <= 35) && (!canPushBox[i]) && (fabs((float)(box.getBoxY(i) - playerY)) <= 57) && (box.getBoxY(i) < playerY))
		{
			return false;
		}
	}
}

bool Player::checkOnMoveDown(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window)
{
	int curRow = calculateCurPlayerRow() + 6;
	int curCol = calculateCurPlayerCol() + 11;
	bool canMoveDown = true;
	const int numOfPointsBoxes = 7;
	checkOnKey(curRow, curCol, 'D');
	checkOnDoor('D', map, anime);
	canMoveDown = checkOnDownBoxCollisions(curRow, curCol, box, map);
	if (anime.getCageAnimationState())
	{
		map.firstLevelMap[12][31] = ' ';
	}
	if (map.firstLevelMap[curRow + 1][curCol] != ' ')
	{
		if ((map.firstLevelMap[curRow + 1][curCol] != 'T') && (map.firstLevelMap[curRow + 1][curCol] != '.') && (map.firstLevelMap[curRow + 1][curCol] != 'G') && returnPlayerY() + 4 >= curRow * brickSize + 30)
		{
			canMoveDown = false;
		}
	}
	canMoveDown = checkOnDownCageCollision(canMoveDown);
	std::fill(canPushBox, canPushBox + numOfPointsBoxes, false);
	return canMoveDown;
}

bool Player::checkOnUpBoxCollisions(int curRow, int curCol, Boxes& box, Map& map)
{
	const int numOfPointsBoxes = 7;
	for (int i = 0; i < numOfPointsBoxes; i++)
	{
		checkOnBox(curRow, curCol, 'U', box, map, i);
		checkOnNearBox(curRow, curCol, 'U', box, map, i);
		if (canPushBox[i])
		{
			box.pushBox(curRow, curCol, 'U', box, i);
		}
		if ((fabs((float)(box.getBoxX(i) - playerX)) <= 40) && (!canPushBox[i]) && (fabs((float)(box.getBoxY(i) - playerY)) <= 60))
		{
			return false;
		}
	}
}

bool Player::checkOnMoveUp(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window)
{
	int curRow = calculateCurPlayerRow() + 6;
	int curCol = calculateCurPlayerCol() + 11;
	bool canMoveUp = true;
	const int numOfPointsBoxes = 7;
	checkOnKey(curRow, curCol, 'U');
	checkOnDoor('U', map, anime);
	canMoveUp = checkOnUpBoxCollisions(curRow, curCol, box, map);
	if (((map.firstLevelMap[curRow - 1][curCol] != ' ') && (map.firstLevelMap[curRow - 1][curCol] != 'T') && (map.firstLevelMap[curRow - 1][curCol] != '.') && (map.firstLevelMap[curRow - 1][curCol] != 'G')) && (returnPlayerY() - 4 <= curRow * brickSize))
	{
		canMoveUp = false;
	}
	std::fill(canPushBox, canPushBox + numOfPointsBoxes, false);
	return canMoveUp;
}

bool Player::checkOnLeftBoxCollisions(int curRow, int curCol, Boxes& box, Map& map)
{
	const int numOfPointsBoxes = 7;
	for (int i = 0; i < numOfPointsBoxes; i++)
	{
		checkOnBox(curRow, curCol, 'L', box, map, i);
		checkOnNearBox(curRow, curCol, 'L', box, map, i);
		if (canPushBox[i])
		{
			box.pushBox(curRow, curCol, 'L', box, i);
		}
		if (playerX < box.getBoxX(i))
		{
			if ((fabs((float)(box.getBoxX(i) - playerX)) <= 30) && (!canPushBox[i]) && (fabs((float)(box.getBoxY(i) - playerY)) <= 55))
			{
				return false;
			}
		}
		else
		{
			if ((fabs((float)(box.getBoxX(i) - playerX)) <= 55) && (!canPushBox[i]) && (fabs((float)(box.getBoxY(i) - playerY)) <= 55))
			{
				return false;
			}
		}
	}
}

bool Player::checkOnMoveLeft(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window)
{
	int curRow = calculateCurPlayerRow() + 6;
	int curCol = calculateCurPlayerCol() + 11;
	bool canMoveLeft = true;
	const int numOfPointsBoxes = 7;
	checkOnKey(curRow, curCol, 'L');
	checkOnDoor('L', map, anime);
	canMoveLeft = checkOnLeftBoxCollisions(curRow, curCol, box, map);
	if (((map.firstLevelMap[curRow][curCol - 1] != ' ') && (map.firstLevelMap[curRow][curCol - 1] != 'T') && (map.firstLevelMap[curRow][curCol - 1] != '.') && (map.firstLevelMap[curRow][curCol - 1] != 'G')) && (returnPlayerX() - 4 <= curCol * brickSize))
	{
		canMoveLeft = false;
	}
	std::fill(canPushBox, canPushBox + numOfPointsBoxes, false);
	return canMoveLeft;
}

bool Player::checkOnRightCageCollision(int curRow, int curCol, bool canMoveRight)
{
	if (returnPlayerY() >= brickSize * 12 - 55)
	{
		canMoveRight = false;
	}
	return canMoveRight;
}

bool Player::checkOnRightBoxCollisions(int curRow, int curCol, Boxes& box, Map& map)
{
	const int numOfPointsBoxes = 7;
	for (int i = 0; i < numOfPointsBoxes; i++)
	{
		checkOnBox(curRow, curCol, 'R', box, map, i);
		checkOnNearBox(curRow, curCol, 'R', box, map, i);
		if (canPushBox[i])
		{
			box.pushBox(curRow, curCol, 'R', box, i);
		}
		if (((fabs((float)(box.boxes[i].x - playerX)) <= 40) && (!canPushBox[i])) && (fabs((float)(box.boxes[i].y - playerY)) <= 50))
		{
			return false;
		}
	}
}

bool Player::checkOnMoveRight(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window)
{
	int curRow = calculateCurPlayerRow() + 6;
	int curCol = calculateCurPlayerCol() + 11;
	bool canMoveRight = true;
	const int numOfPointsBoxes = 7;
	checkOnKey(curRow, curCol, 'R');
	checkOnDoor('R', map, anime);
	canMoveRight = checkOnRightBoxCollisions(curRow, curCol, box, map);
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
	std::fill(canPushBox, canPushBox + numOfPointsBoxes, false);
	return canMoveRight;
}

void Player::checkOnNearBox(int curRow, int curCol, char dir, Boxes& box, Map& map, int indexOfBox)
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

void Player::checkBoxOnWallCollision(Map& map, int curBoxRow, int curBoxCol, char dir, int indexOfBox, Boxes& box)
{
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

void Player::checkOnBox(int curRow, int curCol, char dir, Boxes& box, Map& map, int indexOfBox)
{
	int curXDistance = box.getBoxX(indexOfBox) - 11 * brickSize;
	int curBoxCol = curXDistance / brickSize + 11;

	int curYDistance = box.getBoxY(indexOfBox) + 50 - 6 * brickSize;
	int curBoxRow = curYDistance / brickSize + 6;

	if ((dir == 'R') && (fabs((float)(box.getBoxY(indexOfBox) - playerY)) <= 45) && (fabs((float)(box.getBoxX(indexOfBox) - playerX)) <= 45))
	{
		canPushBox[indexOfBox] = true;
	}
	else if ((box.getBoxX(indexOfBox) > playerX) && (dir == 'L') && (fabs((float)(box.getBoxY(indexOfBox) - playerY)) <= 45) && (fabs((float)(box.getBoxX(indexOfBox) - playerX)) <= 30))
	{
		canPushBox[indexOfBox] = true;
	}
	else if ((box.getBoxX(indexOfBox) < playerX) && (dir == 'L') && (fabs((float)(box.getBoxY(indexOfBox) - playerY)) <= 45) && (fabs((float)(box.getBoxX(indexOfBox) - playerX)) <= 55))
	{
		canPushBox[indexOfBox] = true;
	}
	else if ((dir == 'U') && (fabs((float)(box.getBoxY(indexOfBox) - playerY)) <= 60) && (fabs((float)(box.getBoxX(indexOfBox) - playerX)) <= 40))
	{
		canPushBox[indexOfBox] = true;
	}
	else if ((dir == 'D') && (fabs((float)(box.getBoxY(indexOfBox) - playerY)) <= 57) && (fabs((float)(box.getBoxX(indexOfBox) - playerX)) <= 35))
	{
		canPushBox[indexOfBox] = true;
	}
	else if ((dir == 'D') && (fabs((float)(box.getBoxY(indexOfBox) - playerY)) <= 64) && (fabs((float)(box.getBoxX(indexOfBox) - playerX)) <= 35) && (box.getBoxY(indexOfBox) > playerY))
	{
		canPushBox[indexOfBox] = true;
	}
	else
	{
		canPushBox[indexOfBox] = false;
	}
	checkBoxOnWallCollision(map, curBoxRow, curBoxCol, dir, indexOfBox, box);
}

bool Player::checkOnTeleport(Map& map)
{
	int curRow = calculateCurPlayerRow() + 6;
	int curCol = calculateCurPlayerCol() + 11;

	if (map.firstLevelMap[curRow][curCol] == 'T')
	{
		return true;
	}
	return false;
}

void Player::updateRight(Boxes& box, Animations& cage, Map& map, sf::RenderWindow& window)
{
	if (checkOnMoveRight(box, cage, map, window))
	{
		playerX += offset;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 96, 24, 32));
	}
}

void Player::updateDown(Boxes& box, Animations& cage, Map& map, sf::RenderWindow& window)
{
	if (checkOnMoveDown(box, cage, map, window))
	{
		playerY += offset;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 0, 24, 32));
	}
}

void Player::updateUp(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window)
{
	if (checkOnMoveUp(box, anime, map, window))
	{
		playerY -= offset;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 32, 24, 32));
	}
}

void Player::updateLeft(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window)
{
	if (checkOnMoveLeft(box, anime, map, window))
	{
		playerX -= offset;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 64, 24, 32));
	}
}

bool Player::startTeleportAnimation(Map& map, sf::Clock teleportClock, Animations& animeOfTeleport)
{
	sf::Time curTime = teleportClock.getElapsedTime();
	float timing = curTime.asSeconds();
	if (timing >= animeOfTeleport.getInterval())
	{
		int curRow = calculateCurPlayerRow() + 6;
		int curCol = calculateCurPlayerCol() + 11;

		if (!animeOfTeleport.getFirstCycleInfo())
		{
			map.firstLevelMap[curRow][curCol] = 'B';
		}

		if ((map.getPlateX() < map.startXCoordinate + brickSize * 3) && (curTime.asSeconds() >= animeOfTeleport.getInterval()))
		{
			map.teleportSprite.setPosition(map.getPlateX() - brickSize, map.getPlateY());
			playerX += 3;
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
			playerY -= 3;
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

bool Player::move(sf::RenderWindow& window, Map& map, Animations& anime, Boxes& box, Animations& cage, sf::Clock& playerClock)
{
	sf::Time curTime = playerClock.getElapsedTime();
	float timing = curTime.asMilliseconds();
	if (timing >= playerDelay)//connect to time
	{
		if (!anime.getStay())
		{
			if (curImg > 6)
			{
				curImg = 0;
			}
			switch (playerDir)
			{
			case Direction::down:
			{
				updateDown(box, anime, map, window);
				break;
			}
			case Direction::up:
			{
				updateUp(box, anime, map, window);
				break;
			}
			case Direction::left:
			{
				updateLeft(box, anime, map, window);
				break;
			}
			case Direction::right:
			{
				updateRight(box, anime, map, window);
				break;
			}
			}
			sprite.setPosition(playerX, playerY);
		}
		if (checkOnTeleport(map) && (map.getPlateY() <= 7 * brickSize - 5))
		{
			anime.setStay(true);
		}
		return true;
	}
	return false;
}

bool Player::prepareForTeleportAnime(Animations& animeOfTeleport, Map& map, sf::Clock teleportClock, bool isNewCycle)
{
	if (animeOfTeleport.getStay())
	{
		int curRow = calculateCurPlayerRow() + 6;
		int curCol = calculateCurPlayerCol() + 11;

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
		sprite.setPosition(playerX, playerY);
	}
	return isNewCycle;
}

bool Player::update(sf::Clock clock, Map& map, sf::Clock teleportClock, Animations& animeOfTeleport)
{
	bool isNewCycle = false;
	sf::Time curTime = clock.getElapsedTime();
	if (curTime.asSeconds() >= delayInSeconds)
	{
		curImg = 0;
		switch (playerDir)
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

void Player::checkOnBottomDoor(int curRow, int curCol, Map& map, Animations& doorAnime)
{
	if (map.firstLevelMap[curRow + 1][curCol] == 'D') 
	{
		if ((returnPlayerY() + offset >= (curRow + 1) * brickSize - 60) && isHasKey())
		{
			int numOfDoor = doorAnime.checkCurDoorNum(curRow + 1, curCol);
			doorAnime.setDoorAnimationState(true, numOfDoor);
		}
	}
}

void Player::checkOnTopDoor(int curRow, int curCol, Map& map, Animations& doorAnime)
{
	if (map.firstLevelMap[curRow - 1][curCol] == 'D')
	{
		if ((returnPlayerY() - offset <= curRow * brickSize) && isHasKey())
		{
			int numOfDoor = doorAnime.checkCurDoorNum(curRow - 1, curCol);
			doorAnime.setDoorAnimationState(true, numOfDoor);
		}
	}
}

void Player::checkOnLeftDoor(int curRow, int curCol, Map& map, Animations& doorAnime)
{
	if (map.firstLevelMap[curRow][curCol - 1] == 'D')
	{
		if ((returnPlayerX() - offset <= curCol * brickSize) && isHasKey())
		{
			int numOfDoor = doorAnime.checkCurDoorNum(curRow, curCol - 1);
			doorAnime.setDoorAnimationState(true, numOfDoor);
		}
	}
}

void Player::checkOnRightDoor(int curRow, int curCol, Map& map, Animations& doorAnime)
{
	if (map.firstLevelMap[curRow][curCol + 1] == 'D')
	{
		if ((returnPlayerX() + offset >= (curCol + 1) * brickSize - 45) && isHasKey())
		{
			int numOfDoor = doorAnime.checkCurDoorNum(curRow, curCol + 1);
			doorAnime.setDoorAnimationState(true, numOfDoor);
		}
	}
}

void Player::checkOnDoor(char dir, Map& map, Animations& doorAnime)
{
	int curRow = calculateCurPlayerRow() + 6;
	int curCol = calculateCurPlayerCol() + 11;

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