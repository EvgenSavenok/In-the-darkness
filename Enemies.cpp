#include "Enemies.h"

Enemies::Enemies()
{
	x = brickSize * 28 + 25;
	y = brickSize * 14;
	curImg = 0;
	dir = enemyDirection::left;
	img.loadFromFile("Images/enemy_boar.png");
	texture.loadFromImage(img);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 82, 45, 70));
	sprite.setPosition(x, y);
	sprite.setScale(1.1, 1.1);
}

bool Enemies::checkBoarUp()
{
	int curXDistance = returnEnemyX() - 11 * brickSize;
	int curCol = curXDistance / brickSize + 11;

	int curYDistance = returnEnemyY() + 50 - 6 * brickSize;
	int curRow = curYDistance / brickSize + 6;

	if ((map.firstLevelMap[curRow - 1][curCol] != ' ') && (returnEnemyY() - 4 <= curRow * brickSize))
	{
		return false;
	}
	return true;
}

bool Enemies::checkBoarDown()
{
	int curXDistance = returnEnemyX() - 11 * brickSize;
	int curCol = curXDistance / brickSize + 11;

	int curYDistance = returnEnemyY() + 50 - 6 * brickSize;
	int curRow = curYDistance / brickSize + 6;

	if (((map.firstLevelMap[curRow + 1][curCol] != ' ')) && (returnEnemyX() - 4 <= curCol * Map::brickSize))
	{
		return false;
	}
	return true;
}

bool Enemies::checkBoarRight()
{
	int curXDistance = returnEnemyX() - 11 * brickSize;
	int curCol = curXDistance / brickSize + 11;

	int curYDistance = returnEnemyY() + 50 - 6 * brickSize;
	int curRow = curYDistance / brickSize + 6;

	if (((map.firstLevelMap[curRow][curCol + 1] != ' ')) && (returnEnemyX() - 4 <= curCol * brickSize))
	{
		return false;
	}
	return true;
}

bool Enemies::checkBoarLeft()
{
	int curXDistance = returnEnemyX() - 11 * brickSize;
	int curCol = curXDistance / brickSize + 11;

	int curYDistance = returnEnemyY() + 50 - 6 * brickSize;
	int curRow = curYDistance / brickSize + 6;

	if (((map.firstLevelMap[curRow][curCol - 1] != ' ')) && (returnEnemyX() - 4 <= curCol * Map::brickSize))
	{
		return false;
	}
	return true;
}

enemyDirection Enemies::defineNewDirection(int curNumOfDir)
{
	switch (curNumOfDir)
	{
	case 1:
	{
		if (checkBoarRight())
		{
			return enemyDirection::right;
		}
		break;
	}
	case 2:
	{
		if (checkBoarLeft())
		{
			return enemyDirection::left;
		}
		break;
	}
	case 3:
	{
		if (checkBoarUp())
		{
			return enemyDirection::up;
		}
		break;
	}
	case 4:
	{
		if (checkBoarDown())
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

void Enemies::determineDir()
{
	enemyDirection enemyCurDir = enemyDirection::none;
	do {
		srand(time(NULL));
		int randDir = rand() % 4 + 1;
		enemyCurDir = defineNewDirection(randDir);
	} while (enemyCurDir == enemyDirection::none);
	dir = enemyCurDir;
}

bool Enemies::checkOnMoveDown()
{
	int curXDistance = returnEnemyX() - 11 * brickSize;
	int curCol = curXDistance / brickSize + 11;

	int curYDistance = returnEnemyY() - 6 * brickSize;
	int curRow = curYDistance / brickSize + 6;

	if ((map.firstLevelMap[curRow + 1][curCol] != ' ') && (returnEnemyY() + 25 >= curRow * brickSize + 25))
	{
		determineDir();
		return false;
	}
	return true;
}

bool Enemies::checkOnMoveUp()
{
	int curXDistance = returnEnemyX() - 11 * brickSize;
	int curCol = curXDistance / brickSize + 11;

	int curYDistance = returnEnemyY() + 50 - 6 * brickSize;
	int curRow = curYDistance / brickSize + 6;

	if ((map.firstLevelMap[curRow - 1][curCol] != ' ') && (returnEnemyY() - 4 <= curRow * brickSize))
	{
		determineDir();
		return false;
	}
	return true;
}

bool Enemies::checkOnMoveLeft()
{
	int curXDistance = returnEnemyX() - 11 * brickSize;
	int curCol = curXDistance / brickSize + 11;

	int curYDistance = returnEnemyY() + 50 - 6 * brickSize;
	int curRow = curYDistance / brickSize + 6;

	if (((map.firstLevelMap[curRow][curCol - 1] != ' ')) && (returnEnemyX() - 4 <= curCol * Map::brickSize))
	{
		determineDir();
		return false;
	}
	return true;
}

bool Enemies::checkOnMoveRight()
{
	int curXDistance = returnEnemyX() - 11 * brickSize;
	int curCol = curXDistance / brickSize + 11;

	int curYDistance = returnEnemyY() + 50 - 6 * brickSize;
	int curRow = curYDistance / brickSize + 6;

	if (((map.firstLevelMap[curRow][curCol + 1] != ' ')) && (returnEnemyX() - 4 <= curCol * brickSize + 20))
	{
		determineDir();
		return false;
	}
	return true;
}

bool Enemies::checkOnNearPlayer()
{
	return false;
}

bool Enemies::enemyMove(sf::Clock clock)
{
	sf::Time curTime = clock.getElapsedTime();
	float timing = curTime.asMilliseconds();
	if (timing >= 200)
	{
		if (curImg > 3)
		{
			curImg = 0;
		}
		switch (dir)
		{
		case enemyDirection::down:
		{
			if (checkOnMoveDown())
			{
				y += 6;
				sprite.setTexture(texture);
				sprite.setTextureRect(sf::IntRect(0, curImg * 82 + 10, 45, 80));
				curImg++;
			}
			break;
		}
		case enemyDirection::up:
		{
			if (checkOnMoveUp())
			{
				y -= 6;
				sprite.setTexture(texture);
				sprite.setTextureRect(sf::IntRect(45 * 5 - 30, curImg * 82 + 10, 45, 80));
				curImg++;
			}
			break;
		}
		case enemyDirection::left:
		{
			if (checkOnMoveLeft())
			{
				x -= 8;
				sprite.setTexture(texture);
				sprite.setTextureRect(sf::IntRect(132, curImg * 82 + 8, 60, 82));
				curImg++;
			}
			break;
		}
		case enemyDirection::right:
		{
			if (checkOnMoveRight())
			{
				x += 8;
				sprite.setTexture(texture);
				sprite.setTextureRect(sf::IntRect(0, (curImg * 82) + 4 * 82 + 8, 60, 80));
				curImg++;
			}
			break;
		}
		}
		sprite.setPosition(x, y);
		return true;
	}
	return false;
}