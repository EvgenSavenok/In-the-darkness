#include "Enemies.h"

Enemies::Enemies(int startX, int startY)
{
	enemyX = brickSize * startX + 25;
	enemyY = brickSize * startY;
	curEnemyImg = 0;
	enemyDir = enemyDirection::down;
	enemyImg.loadFromFile("Images/enemy_boar.png");
	enemyTexture.loadFromImage(enemyImg);
	enemySprite.setTexture(enemyTexture);
	enemySprite.setTextureRect(sf::IntRect(0, 82, 45, 70));
	enemySprite.setPosition(enemyX, enemyY);
	//enemySprite.setScale(1.1, 1.1);
	isHasLeftLet = false;
	isHasRightLet = false;
	isHasTopLet = false;
	isHasBottomLet = false;
}

bool Enemies::checkBoarUp(int curCol, int curRow)
{
	if ((map.firstLevelMap[curRow - 1][curCol] != ' ') && (returnEnemyY() - 4 <= curRow * brickSize))
	{
		return false;
	}
	return true;
}

bool Enemies::checkBoarDown(int curCol, int curRow)
{
	if (((map.firstLevelMap[curRow + 1][curCol] != ' ')) && (returnEnemyX() - 4 <= curCol * Map::brickSize))
	{
		return false;
	}
	return true;
}

bool Enemies::checkBoarRight(int curCol, int curRow)
{
	if ((map.firstLevelMap[curRow][curCol + 1] != ' '))
	{
		if (returnEnemyX() + 4 <= curCol * brickSize + 50)
		{
			return false;
		}
	}
	return true;
}

bool Enemies::checkBoarLeft(int curCol, int curRow)
{
	if (((map.firstLevelMap[curRow][curCol - 1] != ' ')) && (returnEnemyX() - 8 <= curCol * brickSize))
	{
		return false;
	}
	return true;
}

enemyDirection Enemies::defineNewDirection(int curNumOfDir, int curCol, int curRow)
{
	switch (curNumOfDir)
	{
	case 1:
	{
		if (checkBoarRight(curCol, curRow))
		{
			return enemyDirection::right;
		}
		break;
	}
	case 2:
	{
		if (checkBoarLeft(curCol, curRow))
		{
			return enemyDirection::left;
		}
		break;
	}
	case 3:
	{
		if (checkBoarUp(curCol, curRow))
		{
			return enemyDirection::up;
		}
		break;
	}
	case 4:
	{
		if (checkBoarDown(curCol, curRow))
		{
			return enemyDirection::down;
		}
		break;
	}
	default:
	{
		return enemyDirection::none;
	}
	}
}

void Enemies::determineDir(int curCol, int curRow)
{
	enemyDirection enemyCurDir = enemyDirection::none;
	do {
		srand(time(NULL));
		int randDir = rand() % 4 + 1;
		enemyCurDir = defineNewDirection(randDir, curCol, curRow);
	} while (enemyCurDir == enemyDirection::none);
	enemyDir = enemyCurDir;
}

void Enemies::checkOnNearPlayer(Player& player)
{
	if ((fabs((float)(enemyX - player.playerX) / 2) <= 30) && (fabs((float)(enemyY - player.playerY) / 2) <= 20) && (enemyX <= player.playerX))
		isFacedWithPlayer = true;
	if ((fabs((float)(enemyX - player.playerX) / 2) <= 15) && (fabs((float)(enemyY - player.playerY) / 2) <= 20) && (enemyX >= player.playerX))
		isFacedWithPlayer = true;
}

void Enemies::startKillingAnimation(char dir, Player& player, SoundManager& sound)
{
	if (isFacedWithPlayer)
	{
		if (curKillingImg > 2)
		{
			sound.playBeatingOfPlayer();
			isFacedWithPlayer = false;
			player.checkLives(sound);
			curKillingImg = 0;
			if (!player.getGameOverState())
				checkOnNearPlayer(player);
		}
		else
		{
			enemySprite.setTexture(enemyTexture);
			switch (dir)
			{
			case 'D':
			{
				enemySprite.setTextureRect(sf::IntRect(270, curKillingImg * 75 + 20, 70, 75));
				break;
			}
			case 'U':
			{
				enemySprite.setTextureRect(sf::IntRect(545, curKillingImg * 75 + 20, 70, 75));
				break;
			}
			case 'L':
			{
				enemySprite.setTextureRect(sf::IntRect(365, curKillingImg * 75 + 20, 70, 75));
				break; 
			}
			case 'R':
			{
				enemySprite.setTextureRect(sf::IntRect(365, curKillingImg * 75 + 285, 70, 75));
				break;
			}
			}
			curKillingImg++;
		}
	}
}

void Enemies::checkOnLetWithPlayer(Player& player)
{
	int curXDistance = returnEnemyX() - curEnemyY * brickSize;
	int curEnemyCol = curXDistance / brickSize + curEnemyY;

	int curYDistance = returnEnemyY() + 50 - curEnemyX * brickSize;
	int curEnemyRow = curYDistance / brickSize + curEnemyX;

	int curPlayerCol = player.calculateCurPlayerCol() + 2;
	int curPlayerRow = player.calculateCurPlayerRow() + 2;

	int differenceCol = fabs(curPlayerCol - curEnemyCol);
	int differenceRow = fabs(curPlayerRow - curEnemyRow);
	int i = 0;
	for (; (i < differenceCol) && (curEnemyCol + i < map.mapWidth) && (curEnemyCol - i > -1); i++)
	{
		if (map.firstLevelMap[curEnemyRow][curEnemyCol + i] != ' ')
		{
			isHasRightLet = true;
		}
		if (map.firstLevelMap[curEnemyRow][curEnemyCol - i] != ' ')
		{
			isHasLeftLet = true;
		}
	}
	i = 0;
	for (; (i < differenceRow) && (curEnemyRow + i < map.mapHeight) && (curEnemyRow - i > -1); i++)
	{
		if (map.firstLevelMap[curEnemyRow + i][curEnemyCol] != ' ')
		{
			isHasBottomLet = true;
		}
		if (map.firstLevelMap[curEnemyRow - i][curEnemyCol] != ' ')
		{
			isHasTopLet = true;
		}
	}
}

void Enemies::checkOnPlayer(Player& player, SoundManager& sound)
{
	const int eyeWidth = 50;
	checkOnLetWithPlayer(player);
	if (!isFacedWithLet)
	{
		if ((fabs((float)(enemyX - player.playerX)) <= brickSize * enemyEye) && (player.playerX > enemyX) && (fabs((float)(enemyY - player.playerY)) <= eyeWidth))
		{
			if (((fabs)((float)(enemyY - player.playerY)) <= brickSize) && (!isHasRightLet))
			{
				if ((sound.roar.getStatus() != sf::Sound::Playing) && (enemyDir != enemyDirection::right))
					sound.playRoar();
				enemyDir = enemyDirection::right;
			}
		}
		if ((fabs((float)(enemyX - player.playerX)) <= brickSize * enemyEye) && (player.playerX < enemyX) && (fabs((float)(enemyY - player.playerY)) <= eyeWidth))
		{
			if ((fabs((float)(enemyY - player.playerY)) <= brickSize) && (!isHasLeftLet))
			{
				if ((sound.roar.getStatus() != sf::Sound::Playing) && (enemyDir != enemyDirection::left))
					sound.playRoar();
				enemyDir = enemyDirection::left;
			}
		}
		if ((fabs((float)(enemyY - player.playerY)) <= brickSize * enemyEye) && (player.playerY > enemyY) && (fabs((float)(enemyX - player.playerX)) <= eyeWidth))
		{
			if ((fabs((float)(enemyX - player.playerX)) <= brickSize) && (!isHasBottomLet))
			{
				if ((sound.roar.getStatus() != sf::Sound::Playing) && (enemyDir != enemyDirection::down))
					sound.playRoar();
				enemyDir = enemyDirection::down;
			}
		}
		if ((fabs((float)(enemyY - player.playerY)) <= brickSize * enemyEye) && (player.playerY < enemyY) && (fabs((float)(enemyX - player.playerX)) <= eyeWidth))
		{
			if ((fabs((float)(enemyX - player.playerX)) <= brickSize) && (!isHasTopLet))
			{
				if ((sound.roar.getStatus() != sf::Sound::Playing) && (enemyDir != enemyDirection::up))
					sound.playRoar();
				enemyDir = enemyDirection::up;
			}
		}
		checkOnNearPlayer(player);
	}
	isHasLeftLet = false;
	isHasRightLet = false;
	isHasTopLet = false;
	isHasBottomLet = false;
}

bool Enemies::checkOnMoveDown(Player& player, int curCol, int curRow, SoundManager& sound)
{
	if (!player.getGameOverState())
	{
		checkOnPlayer(player, sound);
		startKillingAnimation('D', player, sound);
	}
	if ((map.firstLevelMap[curRow + 1][curCol] != ' ') && (returnEnemyY() + 25 >= curRow * brickSize + 25))
	{
		isFacedWithLet = true;
		determineDir(curCol, curRow);
		return false;
	}
	isFacedWithLet = false;
	return true;
}

bool Enemies::checkOnMoveUp(Player& player, int curCol, int curRow, SoundManager& sound)
{
	if (!player.getGameOverState())
	{
		checkOnPlayer(player, sound);
		startKillingAnimation('U', player, sound);
	}
	if ((map.firstLevelMap[curRow - 1][curCol] != ' ') && (returnEnemyY() - 8 <= curRow * brickSize))
	{
		isFacedWithLet = true;
		determineDir(curCol, curRow);
		return false;
	}
	isFacedWithLet = false;
	return true;
}

bool Enemies::checkOnMoveLeft(Player& player, int curCol, int curRow, SoundManager& sound)
{
	if (!player.getGameOverState())
	{
		checkOnPlayer(player, sound);
		startKillingAnimation('L', player, sound);
	}
	if (((map.firstLevelMap[curRow][curCol - 1] != ' ')) && (returnEnemyX() - 8 <= curCol * brickSize))
	{
		if (returnEnemyY() > curRow * brickSize - 55)
		{
			determineDir(curCol, curRow);
			isFacedWithLet = true;
			return false;
		}
	}
	isFacedWithLet = false;
	return true;
}

bool Enemies::checkOnMoveRight(Player& player, int curCol, int curRow, SoundManager& sound)
{
	if (!player.getGameOverState())
	{
		checkOnPlayer(player, sound);
		startKillingAnimation('R', player, sound);
	}
	//выход за границы массива
	if ((map.firstLevelMap[curRow][curCol + 1] != ' ') && (returnEnemyX() + 8 >= curCol * brickSize + 30))
	{ 
		if (returnEnemyY() > curRow * brickSize - 55)
		{ 
			isFacedWithLet = true;
			determineDir(curCol, curRow);
			return false;
		}
	}
	isFacedWithLet = false;
	return true;
}

bool Enemies::enemyMove(sf::Clock clock, Player& player, SoundManager& sound)
{
	sf::Time curTime = clock.getElapsedTime();
	float timing = curTime.asMilliseconds();
	if (timing >= 200)
	{
		if (curEnemyImg > 3)
		{
			curEnemyImg = 0;
		}

		int curXDistance = returnEnemyX() - curEnemyY * brickSize;
		int curCol = curXDistance / brickSize + curEnemyY;

		int curYDistance = returnEnemyY() + 50 - curEnemyX * brickSize;
		int curRow = curYDistance / brickSize + curEnemyX;

		switch (enemyDir)
		{
		case enemyDirection::down:
		{
			if (checkOnMoveDown(player, curCol, curRow, sound) && !isFacedWithPlayer)
			{
				enemyY += enemyStep;
				enemySprite.setTexture(enemyTexture);
				enemySprite.setTextureRect(sf::IntRect(0, curEnemyImg * 82 + 10, 45, 80));
				curEnemyImg++;
			}
			break;
		}
		case enemyDirection::up:
		{
			if (checkOnMoveUp(player, curCol, curRow, sound) && !isFacedWithPlayer)
			{
				enemyY -= enemyStep;
				enemySprite.setTexture(enemyTexture);
				enemySprite.setTextureRect(sf::IntRect(45 * 5 - 30, curEnemyImg * 82 + 10, 45, 80));
				curEnemyImg++;
			}
			break;
		}
		case enemyDirection::left:
		{
			if (checkOnMoveLeft(player, curCol, curRow, sound) && !isFacedWithPlayer)
			{
				enemyX -= enemyStep;
				enemySprite.setTexture(enemyTexture);
				enemySprite.setTextureRect(sf::IntRect(132, curEnemyImg * 82 + 8, 60, 82));
				curEnemyImg++;
			}
			break;
		}
		case enemyDirection::right:
		{
			if (checkOnMoveRight(player, curCol, curRow, sound) && !isFacedWithPlayer)
			{
				enemyX += enemyStep;
				enemySprite.setTexture(enemyTexture);
				enemySprite.setTextureRect(sf::IntRect(0, (curEnemyImg * 82) + 4 * 82 + 8, 60, 80));
				curEnemyImg++;
			}
			break;
		}
		}
		enemySprite.setPosition(enemyX, enemyY);
		return true;
	}
	return false;
}