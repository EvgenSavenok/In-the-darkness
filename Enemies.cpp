#include "Enemies.h"

Enemies::Enemies()
{
	x = brickSize * 20 + 25;
	y = brickSize * 17;
	curImg = 0;
	dir = enemyDirection::down;
	img.loadFromFile("Images/enemy_boar.png");
	texture.loadFromImage(img);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 82, 45, 70));
	sprite.setPosition(x, y);
	sprite.setScale(1.2, 1.2);
}

bool Enemies::checkOnMoveDown()
{
	Map map;

	int curXDistance = returnEnemyX() - 11 * Map::brickSize;
	int curCol = curXDistance / Map::brickSize;

	int curYDistance = returnEnemyY() - 6 * Map::brickSize;
	int curRow = curYDistance / Map::brickSize;

	curCol += 11;
	curRow += 6;

	if ((map.firstLevelMap[curRow + 1][curCol] != ' ') && (returnEnemyY() + 25 >= curRow * Map::brickSize + 25))
	{
		return false;
	}
	return true;
}

bool Enemies::checkOnMoveUp()
{
	Map map;

	int curXDistance = returnEnemyX() - 11 * Map::brickSize;
	int curCol = curXDistance / Map::brickSize;

	int curYDistance = returnEnemyY() + 50 - 6 * Map::brickSize;
	int curRow = curYDistance / Map::brickSize;

	curCol += 11;
	curRow += 6;

	if ((map.firstLevelMap[curRow - 1][curCol] != ' ') && (returnEnemyY() - 4 <= curRow * Map::brickSize))
	{
		return false;
	}
	return true;
}

bool Enemies::checkOnMoveLeft()
{
	Map map;

	int curXDistance = returnEnemyX() - 11 * Map::brickSize;
	int curCol = curXDistance / Map::brickSize;

	int curYDistance = returnEnemyY() + 50 - 6 * Map::brickSize;
	int curRow = curYDistance / Map::brickSize;

	curCol += 11;
	curRow += 6;

	if (((map.firstLevelMap[curRow][curCol - 1] != ' ')) && (returnEnemyX() - 4 <= curCol * Map::brickSize))
	{
		return false;
	}
	return true;
}

bool Enemies::checkOnMoveRight()
{
	Map map;

	int curXDistance = returnEnemyX() - 11 * Map::brickSize;
	int curCol = curXDistance / Map::brickSize;

	int curYDistance = returnEnemyY() + 50 - 6 * Map::brickSize;
	int curRow = curYDistance / Map::brickSize;

	curCol += 11;
	curRow += 6;

	if (((map.firstLevelMap[curRow][curCol + 1] != ' ')) && (returnEnemyX() - 4 <= curCol * Map::brickSize))
	{
		return false;
	}
	return true;
}

bool Enemies::enemyMove(sf::Clock clock)
{
	sf::Time curTime = clock.getElapsedTime();
	float timing = curTime.asSeconds();
	if (timing >= delayInSeconds)
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
				y += 4;
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
				y -= 4;
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
				x -= 4;
				sprite.setTexture(texture);
				sprite.setTextureRect(sf::IntRect(48, curImg * 82 + 8, 50, 80));
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