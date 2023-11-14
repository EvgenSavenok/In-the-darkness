#include "Player.h"

Player::Player()
{
	key = false;
	std::fill(canPushBox, canPushBox + 7, false);
	playerX = brickSize * startPlayerX + 25; 
	playerY = brickSize * startPlayerY + 15;
	curImg = 0;
	playerDir = Direction::down;
	playerImg.loadFromFile("Images/player.png");
	texture.loadFromImage(playerImg);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 24, 32));
	sprite.setPosition(playerX, playerY);
	sprite.setScale(1.9, 1.9);

	keyX = brickSize * 31 + 30;
	keyY = brickSize * 8 + 30;
	keySprite.setPosition(keyX, keyY);

	keyImg.loadFromFile("Images/card-key.png");
	keyTexture.loadFromImage(keyImg);
	keySprite.setTexture(keyTexture);
	keySprite.setTextureRect(sf::IntRect(0, 0, 30, 30));

	deadPlayerImg.loadFromFile("Images/dead_man.png");
	deadPlayerTexture.loadFromImage(deadPlayerImg);

    lifeBarImg.loadFromFile("Images/life_bar.png");
	lifeBarTexture.loadFromImage(lifeBarImg);
	lifeBarSprite.setTexture(lifeBarTexture);
	lifeBarSprite.setTextureRect(sf::IntRect(0, 0, widthOfLifeBar, 77));

	deathTextImg.loadFromFile("Images/deathText.png");
	deathTextTexture.loadFromImage(deathTextImg);
	deathTextSprite.setTexture(deathTextTexture);
}

void Player::resetPlayer()
{
	if (!isHasSavePoint)
		key = false;
	if (isGameWin)
	{
		savePointX = 12;
		savePointY = 6;
	}
	else
	{
		savePointX = 29;
		savePointY = 10;
	}
	std::fill(canPushBox, canPushBox + 7, false);
	playerX = brickSize * startPlayerX + 25;
	playerY = brickSize * startPlayerY + 15;
	sprite.setPosition(playerX, playerY);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, 24, 32));
	curImg = 0;

	playerDir = Direction::down;

	keyX = brickSize * 31 + 30;
	keyY = brickSize * 8 + 30;
	keySprite.setPosition(keyX, keyY);

	widthOfLifeBar = 190;
	lifeBarSprite.setTextureRect(sf::IntRect(0, 0, widthOfLifeBar, 77));

	numOfLives = startNumOfLives;
	setGameOverState(false);
    isGameWin = false;
}

void Player::resetTeleport(Animations& anime, Map& map)
{
	anime.setStay(false);
	anime.setInterval(1.5);
	anime.setFirstCycleInfo(false);
	anime.setFirstSetInfo(true);
	map.firstLevelMap[7][13] = 'T';
	map.firstLevelMap[7][13 + 3] = 'B';
	map.setPlateX(-1);
	map.setPlateY(-1);
}

void Player::resetCageAnimation(Animations& anime, Map& map)
{
	if (!isHasSavePoint)
	{
		anime.setCageAnimationState(false);
		anime.setCageHeight(brickSize);
		int cageX = 8;
		int cageY = 31;
		map.firstLevelMap[cageX][cageY] = 'C';
		anime.getCageSprite().setTextureRect(sf::IntRect(0, 0, 90, anime.getCageHeight()));
	}
}

void Player::resetBoxes(Boxes& box, Map& map)
{
	if (!isHasSavePoint)
	{
		box.boxes.clear();
		box.initializeBoxes();
		for (int i = 0; i < box.greenPointsCoordinates.size(); i++)
		{
			int x = box.greenPointsCoordinates[i].x;
			int y = box.greenPointsCoordinates[i].y;
			map.firstLevelMap[x][y] = '.';
		}
	}
}

void Player::resetSounds(SoundManager& sound)
{
	sound.setPowerDownSound(true);
}

void Player::resetGame(Map& map, Animations& anime, Boxes& box, SoundManager& sound)
{
	resetPlayer();
	anime.resetMap(map, anime);
	resetTeleport(anime, map);
	resetCageAnimation(anime, map);
	resetBoxes(box, map);
	resetSounds(sound);
}

void Player::checkLives(SoundManager& sound)
{
	numOfLives--;
	lifeBarSprite.setTextureRect(sf::IntRect(0, 0, widthOfLifeBar -= (widthOfLifeBar / (startNumOfLives)), 77));
	if (numOfLives == 0)
	{
		sound.playDeathSound();
		sprite.setTexture(deadPlayerTexture);
		sprite.setTextureRect(sf::IntRect(0, 0, 33, 20));
		setGameOverState(true);
	}
}

void Player::drawLives(sf::RenderWindow& window, sf::View& camera)
{
	int lifeBarOffsetX = 900;
	int lifeBarOffsetY = 400;
	lifeBarSprite.setPosition(camera.getCenter().x - lifeBarOffsetX, camera.getCenter().y + lifeBarOffsetY);
}

void Player::drawKey(sf::RenderWindow& window)
{
	const int curKeyX = 31;
	const int curKeyY = 8;
	const int keyOffset = 30;
	keyX = brickSize * curKeyX + keyOffset;
	keyY = brickSize * curKeyY + keyOffset;
	keySprite.setPosition(keyX, keyY);

	if (!isHasKey())
	{
		window.draw(keySprite);
	}
}

void Player::checkOnKey(int curRow, int curCol, char curDir, SoundManager& sound)
{
	int curXDistance = returnKeyX() - colOffset * brickSize;
	int curKeyCol = curXDistance / brickSize + colOffset;

	int curYDistance = returnKeyY() + 50 - rowOffset * brickSize;
	int curKeyRow = curYDistance / brickSize + rowOffset;

	const int keyYOffset = 20;
	const int keyXOffset = 10;

	if (curDir == 'D')
	{
		if ((fabs((float)(keyY - playerY)) <= keyYOffset) && (fabs((float)(keyX - playerX)) <= keyXOffset) && (!key))
		{
			key = true;
			sound.playTakingKey();
		}
	}
	if (curDir == 'U') 
	{
		if ((fabs((float)(keyY - playerY)) <= keyYOffset) && (fabs((float)(keyX - playerX)) <= keyXOffset) && (!key))
		{
			key = true;
			sound.playTakingKey();
		}
	}
	if (curDir == 'L')
	{
		if ((fabs((float)(keyX - playerX)) <= keyYOffset) && (fabs((float)(keyY - playerY)) <= keyYOffset) && (!key))
		{
			key = true;
			sound.playTakingKey();
		}
	}	
	if (curDir == 'R')
	{
		if ((fabs((float)(keyX - playerX)) <= keyYOffset) && (fabs((float)(keyY - playerY)) <= keyYOffset) && (!key))
		{
			key = true;
			sound.playTakingKey();
		}
	}
}

int Player::calculateCurPlayerRow()
{
	int curYDistance = returnPlayerY() - rowOffset * Map::brickSize;
	int curRow = curYDistance / Map::brickSize;
	return curRow;
}

int Player::calculateCurPlayerCol()
{
	int curXDistance = returnPlayerX() - colOffset * Map::brickSize;
	int curCol = curXDistance / Map::brickSize;
	return curCol;
}

bool Player::checkOnDownCageCollision(bool canMoveDown, Animations& cage, Map map)
{
	const int cageX = 31;
	const int cageY = 8;
	const int cageXOffset = 30;
	const int cageYOffset = 55;
	int curRow = calculateCurPlayerRow() + rowOffset;
	int curCol = calculateCurPlayerCol() + colOffset;
	if ((returnPlayerY() + playerStep >= brickSize * cageY - cageYOffset) && (map.firstLevelMap[curRow + 1][curCol] == 'C'))
	{
		if ((returnPlayerX() >= brickSize * cageX - cageXOffset) && (returnPlayerX() <= brickSize * cageX + 90))
		{
			canMoveDown = false;
		}
	}
	return canMoveDown;
}

bool Player::checkOnDownBoxCollisions(int curRow, int curCol, Boxes& box, Map& map)
{
	const int numOfPointsBoxes = 6;
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

bool Player::checkOnMoveDown(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window, SoundManager& sound)
{
	int curRow = calculateCurPlayerRow() + rowOffset;
	int curCol = calculateCurPlayerCol() + colOffset;
	bool canMoveDown = true;
	const int numOfPointsBoxes = 6;
	checkOnKey(curRow, curCol, 'D', sound);
	checkOnDoor('D', map, anime, sound);
	checkOnSavePoint(curRow, curCol, sound);
	canMoveDown = checkOnDownBoxCollisions(curRow, curCol, box, map);
	if (anime.getCageAnimationState())
	{
		map.firstLevelMap[12][31] = ' ';
	}
	if (map.firstLevelMap[curRow + 1][curCol] != ' ')
	{
		if ((map.firstLevelMap[curRow + 1][curCol] != 'T') && (map.firstLevelMap[curRow + 1][curCol] != '.') && (map.firstLevelMap[curRow + 1][curCol] != 'G') && (returnPlayerY() + 4 >= curRow * brickSize + 30))
		{
			if (map.firstLevelMap[curRow + 1][curCol] != 'I')
				canMoveDown = false;
		}
	}
	canMoveDown = checkOnDownCageCollision(canMoveDown, anime, map);
	std::fill(canPushBox, canPushBox + numOfPointsBoxes, false);
	return canMoveDown;
}

bool Player::checkOnUpBoxCollisions(int curRow, int curCol, Boxes& box, Map& map)
{
	const int numOfPointsBoxes = 6;
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

bool Player::checkOnMoveUp(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window, SoundManager& sound)
{
	int curRow = calculateCurPlayerRow() + rowOffset;
	int curCol = calculateCurPlayerCol() + colOffset;
	bool canMoveUp = true;
	const int numOfPointsBoxes = 6;
	checkOnExit(map, curRow, curCol, 'U', sound);
	checkOnKey(curRow, curCol, 'U', sound);
	checkOnDoor('U', map, anime, sound);
	checkOnSavePoint(curRow, curCol, sound);
	canMoveUp = checkOnUpBoxCollisions(curRow, curCol, box, map);
	if (((map.firstLevelMap[curRow - 1][curCol] != ' ') && (map.firstLevelMap[curRow - 1][curCol] != 'T') && (map.firstLevelMap[curRow - 1][curCol] != '.') && (map.firstLevelMap[curRow - 1][curCol] != 'G')) && (returnPlayerY() - 4 <= curRow * brickSize))
	{
		if ((map.firstLevelMap[curRow - 1][curCol] != 'I') && (map.firstLevelMap[curRow - 1][curCol] != 'E'))
			canMoveUp = false;
	}
	std::fill(canPushBox, canPushBox + numOfPointsBoxes, false);
	return canMoveUp;
}

bool Player::checkOnLeftBoxCollisions(int curRow, int curCol, Boxes& box, Map& map)
{
	const int numOfPointsBoxes = 6;
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

bool Player::checkOnMoveLeft(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window, SoundManager& sound)
{
	int curRow = calculateCurPlayerRow() + rowOffset;
	int curCol = calculateCurPlayerCol() + colOffset;
	bool canMoveLeft = true;
	const int numOfPointsBoxes = 6;
	checkOnKey(curRow, curCol, 'L', sound);
	checkOnDoor('L', map, anime, sound);
	checkOnSavePoint(curRow, curCol, sound);
	canMoveLeft = checkOnLeftBoxCollisions(curRow, curCol, box, map);
	if (((map.firstLevelMap[curRow][curCol - 1] != ' ')))
	{
		if (map.firstLevelMap[curRow][curCol - 1] != 'T')
		{
			if (map.firstLevelMap[curRow][curCol - 1] != 'G')
			{
				if (map.firstLevelMap[curRow][curCol - 1] != '.')
				{
					if (returnPlayerX() - 4 <= curCol * brickSize)
					{
						if (map.firstLevelMap[curRow][curCol - 1] != 'I')
							canMoveLeft = false;
					}
				}
			}
		}
	}
	std::fill(canPushBox, canPushBox + numOfPointsBoxes, false);
	return canMoveLeft;
}

bool Player::checkOnRightCageCollision(int curRow, int curCol, bool canMoveRight, Map map)
{
	const int cageX = 31;
	const int cageY = 8;
	const int cageXOffset = 55;
	const int cageYOffset = 20;
	if (returnPlayerX() + playerStep >= brickSize * cageX - cageXOffset)
	{
		if (returnPlayerY() + 50 >= brickSize * cageY)
		{
			canMoveRight = false;
		}
	}
	return canMoveRight;
}

bool Player::checkOnRightBoxCollisions(int curRow, int curCol, Boxes& box, Map& map)
{
	const int numOfPointsBoxes = 6;
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

bool Player::checkOnMoveRight(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window, SoundManager& sound)
{
	int curRow = calculateCurPlayerRow() + rowOffset;
	int curCol = calculateCurPlayerCol() + colOffset;
	bool canMoveRight = true;
	const int numOfPointsBoxes = 6;
	checkOnKey(curRow, curCol, 'R', sound);
	checkOnDoor('R', map, anime, sound);
	checkOnSavePoint(curRow, curCol, sound);
	canMoveRight = checkOnRightBoxCollisions(curRow, curCol, box, map);
	if (anime.getCageAnimationState())
	{
		map.firstLevelMap[12][31] = ' ';
	}
	if (((map.firstLevelMap[curRow][curCol + 1] != ' ') && (map.firstLevelMap[curRow][curCol + 1] != 'T') && (map.firstLevelMap[curRow][curCol + 1] != '.') && (map.firstLevelMap[curRow][curCol + 1] != 'G')) && (returnPlayerX() + playerStep >= curCol * brickSize + 45))
	{
		if ((map.firstLevelMap[curRow][curCol + 1] != 'I'))
			canMoveRight = false;
	}
	if (((map.firstLevelMap[curRow][curCol + 1] == 'C') || (map.firstLevelMap[curRow + 1][curCol + 1] == 'C')) && (returnPlayerX() + playerStep >= curCol * brickSize + 45))
	{
		if (!anime.getCageAnimationState())
			canMoveRight = checkOnRightCageCollision(curRow, curCol, canMoveRight, map);
	}
	std::fill(canPushBox, canPushBox + numOfPointsBoxes, false);
	return canMoveRight;
}

void Player::checkOnNearBox(int curRow, int curCol, char dir, Boxes& box, Map& map, int indexOfBox)
{
	if (canPushBox[indexOfBox])
	{
		for (int i = 0; i < 6; i++)
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
	int curXDistance = box.getBoxX(indexOfBox) - colOffset * brickSize;
	int curBoxCol = curXDistance / brickSize + colOffset;

	int curYDistance = box.getBoxY(indexOfBox) + 50 - rowOffset * brickSize;
	int curBoxRow = curYDistance / brickSize + rowOffset;

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
	int curRow = calculateCurPlayerRow() + rowOffset;
	int curCol = calculateCurPlayerCol() + colOffset;

	if (map.firstLevelMap[curRow][curCol] == 'T')
	{
		return true;
	}
	return false;
}

void Player::updateRight(Boxes& box, Animations& cage, Map& map, sf::RenderWindow& window, SoundManager& doorSound)
{
	if (checkOnMoveRight(box, cage, map, window, doorSound))
	{
		playerX += playerStep;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 96, 24, 32));
	}
}

void Player::updateDown(Boxes& box, Animations& cage, Map& map, sf::RenderWindow& window, SoundManager& doorSound)
{
	if (checkOnMoveDown(box, cage, map, window, doorSound))
	{
		playerY += playerStep;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 0, 24, 32));
	}
}

void Player::updateUp(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window, SoundManager& doorSound)
{
	if (checkOnMoveUp(box, anime, map, window, doorSound))
	{
		playerY -= playerStep;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 32, 24, 32));
	}
}

void Player::updateLeft(Boxes& box, Animations& anime, Map& map, sf::RenderWindow& window, SoundManager& doorSound)
{
	if (checkOnMoveLeft(box, anime, map, window, doorSound))
	{
		playerX -= playerStep;
		curImg++;
		sprite.setTexture(texture);
		sprite.setTextureRect(sf::IntRect(curImg * 24, 64, 24, 32));
	}
}

bool Player::startTeleportAnimation(Map& map, sf::Clock teleportClock, Animations& animeOfTeleport, SoundManager& sound)
{
	sf::Time curTime = teleportClock.getElapsedTime();
	float timing = curTime.asSeconds();
	if (timing >= animeOfTeleport.getInterval())
	{
		int curRow = calculateCurPlayerRow() + rowOffset;
		int curCol = calculateCurPlayerCol() + colOffset;

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
				if (sound.teleport.getStatus() != sf::Sound::Playing)
					sound.playTeleportMoving();
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
		int maxTeleportCol = 16;
		if (curCol == maxTeleportCol)
		{
			map.firstLevelMap[curRow][curCol] = 'T';
			animeOfTeleport.setStay(false);
			sound.teleport.stop(); 
		}
		return true;
	}
	return false;
}

bool Player::prepareForTeleportAnime(Animations& animeOfTeleport, Map& map, sf::Clock teleportClock, bool isNewCycle, SoundManager& sound)
{
	int curRow = calculateCurPlayerRow() + rowOffset;
	int curCol = calculateCurPlayerCol() + colOffset;
	if (animeOfTeleport.getStay())
	{
		if (animeOfTeleport.getFirstSetInfo())
		{
			map.startXCoordinate = brickSize * (curCol + 1);
			map.startYCoordinate = brickSize * curRow;
			map.setPlateX(map.startXCoordinate);
			map.setPlateY(map.startYCoordinate);
			animeOfTeleport.setFirstSetInfo(false);
		}
		if (startTeleportAnimation(map, teleportClock, animeOfTeleport, sound))
		{
			isNewCycle = true;
		}
		sprite.setPosition(playerX, playerY);
	}
	int teleportX = 13;
	int teleportY = 7;
	if (!animeOfTeleport.getStay() && (fabs(curRow - teleportY) > 3) && (fabs(curCol - teleportX) > 3))
	{
		resetTeleport(animeOfTeleport, map);

	}
	return isNewCycle;
}

void Player::checkOnGameOver(sf::View& camera, sf::RenderWindow& window)
{
	if (isGameOver)
	{
		const float screenWidth = sf::VideoMode::getDesktopMode().width;
		const float screenHeight = sf::VideoMode::getDesktopMode().height;
		deathTextSprite.setPosition(camera.getCenter().x - 170, camera.getCenter().y + 300);
		window.draw(deathTextSprite);
	}
}

bool Player::update(sf::Clock clock, Map& map, sf::Clock teleportClock, Animations& animeOfTeleport, sf::RenderWindow& window, sf::View& camera, SoundManager& sound)
{
	if (sound.getPowerdownSound())
	{
		sound.playPowerdownSound();
		sound.setPowerDownSound(false);
	}
	bool isNewCycle = false;
	sf::Time curTime = clock.getElapsedTime();
	if ((curTime.asSeconds() >= delayInSeconds) && (!getGameOverState()))
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
	drawLives(window, camera);
	isNewCycle = prepareForTeleportAnime(animeOfTeleport, map, teleportClock, isNewCycle, sound);
	return isNewCycle;
}

void Player::checkOnBottomDoor(int curRow, int curCol, Map& map, Animations& doorAnime, SoundManager& doorSound)
{
	if (map.firstLevelMap[curRow + 1][curCol] == 'D') 
	{
		if ((returnPlayerY() + playerStep >= (curRow + 1) * brickSize - 60) && isHasKey())
		{
			int numOfDoor = doorAnime.checkCurDoorNum(curRow + 1, curCol);
			doorAnime.setDoorAnimationState(true, numOfDoor);
			doorSound.playOpeningOfDoor();
		}
	}
}

void Player::checkOnTopDoor(int curRow, int curCol, Map& map, Animations& doorAnime, SoundManager& doorSound)
{
	if (map.firstLevelMap[curRow - 1][curCol] == 'D')
	{
		if ((returnPlayerY() - playerStep <= curRow * brickSize) && isHasKey())
		{
			int numOfDoor = doorAnime.checkCurDoorNum(curRow - 1, curCol);
			doorAnime.setDoorAnimationState(true, numOfDoor);
			doorSound.playOpeningOfDoor();
		}
	}
}

void Player::checkOnLeftDoor(int curRow, int curCol, Map& map, Animations& doorAnime, SoundManager& doorSound)
{
	if (map.firstLevelMap[curRow][curCol - 1] == 'D')
	{
		if ((returnPlayerX() - playerStep <= curCol * brickSize) && isHasKey())
		{
			int numOfDoor = doorAnime.checkCurDoorNum(curRow, curCol - 1);
			doorAnime.setDoorAnimationState(true, numOfDoor);
			doorSound.playOpeningOfDoor();
		}
	}
}

void Player::checkOnRightDoor(int curRow, int curCol, Map& map, Animations& doorAnime, SoundManager& doorSound)
{
	if (map.firstLevelMap[curRow][curCol + 1] == 'D')
	{
		if ((returnPlayerX() + playerStep >= (curCol + 1) * brickSize - 45) && isHasKey())
		{
			int numOfDoor = doorAnime.checkCurDoorNum(curRow, curCol + 1);
			doorAnime.setDoorAnimationState(true, numOfDoor);
			doorSound.playOpeningOfDoor();
		}
	}
}

void Player::checkOnDoor(char dir, Map& map, Animations& doorAnime, SoundManager& doorSound)
{
	int curRow = calculateCurPlayerRow() + rowOffset;
	int curCol = calculateCurPlayerCol() + colOffset;

	switch (dir)
	{
	case 'D':
	{
		checkOnBottomDoor(curRow, curCol, map, doorAnime, doorSound);
		break;
	}
	case 'U':
	{
		checkOnTopDoor(curRow, curCol, map, doorAnime, doorSound);
		break;
	}
	case 'L':
	{
		checkOnLeftDoor(curRow, curCol, map, doorAnime, doorSound);
		break;
	}
	case 'R':
	{
		checkOnRightDoor(curRow, curCol, map, doorAnime, doorSound);
		break;
	}
	}
}

void Player::checkOnSavePoint(int curRow, int curCol, SoundManager& sound)
{
	if ((curCol == savePointX) && (curRow == savePointY))
	{
		startPlayerX = savePointX;
		startPlayerY = savePointY;
		isHasSavePoint = true;
	}
}

void Player::checkOnExit(Map& map, int curRow, int curCol, char dir, SoundManager& sound)
{
	switch (dir)
	{
	case 'U':
	{
		if ((map.firstLevelMap[curRow - 1][curCol] == 'E') && ((playerY - curRow * brickSize) <= -60))
		{
			isGameWin = true;
			map.isOnceWin = true;
		}
		break;
	}
	}
}

bool Player::move(sf::RenderWindow& window, Map& map, Animations& anime, Boxes& box, Animations& cage, sf::Clock& playerClock, SoundManager& sound)
{
	sf::Time curTime = playerClock.getElapsedTime();
	float timing = curTime.asMilliseconds();
	if (timing >= playerDelay)
	{
		if (!anime.getStay() && (!getGameOverState()))
		{
			if (curImg > 6)
			{
				curImg = 0;
			}
			switch (playerDir)
			{
			case Direction::down:
			{
				updateDown(box, anime, map, window, sound);
				break;
			}
			case Direction::up:
			{
				updateUp(box, anime, map, window, sound);
				break;
			}
			case Direction::left:
			{
				updateLeft(box, anime, map, window, sound);
				break;
			}
			case Direction::right:
			{
				updateRight(box, anime, map, window, sound);
				break;
			}
			}
			sprite.setPosition(playerX, playerY);
		}
		if (checkOnTeleport(map) && (map.getPlateY() <= 2 * brickSize - 5))
		{
			anime.setStay(true);
		}
		return true;
	}
	return false;
}