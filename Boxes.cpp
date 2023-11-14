#include "Boxes.h"

Boxes::Boxes()
{
	boxImg.loadFromFile("Images/box.png");
	boxTexture.loadFromImage(boxImg);
	boxSprite.setTexture(boxTexture);
	boxSprite.setTextureRect(sf::IntRect(0, 0, 60, 60));

	initializeBoxes();
}

void Boxes::initializeBoxes()
{
	boxPosition = sf::Vector2f(brickSize * 27 + 15, brickSize * 3 + 15);
	boxes.push_back(boxPosition);

	boxPosition = sf::Vector2f(brickSize * 28 + 15, brickSize * 4 + 15);
	boxes.push_back(boxPosition);

	boxPosition = sf::Vector2f(brickSize * 28 + 15, brickSize * 5 + 15);
	boxes.push_back(boxPosition);

	boxPosition = sf::Vector2f(brickSize * 29 + 15, brickSize * 7 + 15);
	boxes.push_back(boxPosition);

	boxPosition = sf::Vector2f(brickSize * 27 + 15, brickSize * 7 + 15);
	boxes.push_back(boxPosition);

	boxPosition = sf::Vector2f(brickSize * 25 + 15, brickSize * 7 + 15);
	boxes.push_back(boxPosition);
}

void Boxes::drawBox(sf::RenderWindow& window)
{
	for (int i = 0; i < 6; i++)
	{
		boxSprite.setPosition(getBoxX(i), getBoxY(i));
		window.draw(boxSprite);
	}
}

void Boxes::pushBox(int curRow, int curCol, char dir, Boxes& box, int indexOfBox)
{
	if (dir == 'R')
	{
		setBoxX(getBoxX(indexOfBox) + offset, indexOfBox);
		boxSprite.setPosition(getBoxX(indexOfBox), getBoxY(indexOfBox));
	}
	if (dir == 'L')
	{
		setBoxX(getBoxX(indexOfBox) - offset, indexOfBox);
		boxSprite.setPosition(getBoxX(indexOfBox), getBoxY(indexOfBox));
	}
	if (dir == 'U')
	{
		setBoxY(getBoxY(indexOfBox) - offset, indexOfBox);
		boxSprite.setPosition(getBoxY(indexOfBox), getBoxY(indexOfBox));
	}
	if (dir == 'D')
	{
		setBoxY(getBoxY(indexOfBox) + offset, indexOfBox);
		boxSprite.setPosition(getBoxY(indexOfBox), getBoxY(indexOfBox));
	}
}

void Boxes::checkAllPoints(Map& map)
{
	for (int i = 0; i < 6; i++)
	{
		int curXDistance = getBoxX(i) - 11 * brickSize;
		int curBoxCol = curXDistance / brickSize + 11;

		int curYDistance = getBoxY(i) + 50 - 2 * brickSize;
		int curBoxRow = curYDistance / brickSize + 2;

		if (map.firstLevelMap[curBoxRow][curBoxCol] == '.')
		{
			if ((getBoxX(i) > brickSize * curBoxCol + 12) && (getBoxX(i) < brickSize * curBoxCol + 30)) 
			{
				if ((getBoxY(i) < brickSize * curBoxRow + 30) && (getBoxY(i) > brickSize * curBoxRow))
				{
					map.firstLevelMap[curBoxRow][curBoxCol] = 'G';
					sf::Vector2f bufferPos;
					bufferPos.x = curBoxRow;
					bufferPos.y = curBoxCol;
					greenPointsCoordinates.push_back(bufferPos);
				}
			}
		}
		if (map.firstLevelMap[curBoxRow][curBoxCol] == 'G')
		{
			if ((getBoxX(i) > brickSize * curBoxCol + 30) || (getBoxX(i) < brickSize * curBoxCol + 5))
			{
				map.firstLevelMap[curBoxRow][curBoxCol] = '.';
			}
			if ((getBoxY(i) > brickSize * curBoxRow + 30) || (getBoxY(i) < brickSize * curBoxRow + 5))
			{
				map.firstLevelMap[curBoxRow][curBoxCol] = '.';
			}
		}
	}
}