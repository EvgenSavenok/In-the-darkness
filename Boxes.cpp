#include "Boxes.h"
#include "Map.h"

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
	position = sf::Vector2f(brickSize * 27 + 15, brickSize * 7 + 15);
	boxes.push_back(position);

	position = sf::Vector2f(brickSize * 28 + 15, brickSize * 8 + 15);
	boxes.push_back(position);

	position = sf::Vector2f(brickSize * 28 + 15, brickSize * 9 + 15);
	boxes.push_back(position);

	position = sf::Vector2f(brickSize * 29 + 15, brickSize * 11 + 15);
	boxes.push_back(position);

	position = sf::Vector2f(brickSize * 28 + 15, brickSize * 11 + 15);
	boxes.push_back(position);

	position = sf::Vector2f(brickSize * 27 + 15, brickSize * 11 + 15);
	boxes.push_back(position);

	position = sf::Vector2f(brickSize * 25 + 15, brickSize * 11 + 15);
	boxes.push_back(position);
}

void Boxes::drawBox(sf::RenderWindow& window)
{
	for (int i = 0; i < 7; i++)
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
	for (int i = 0; i < 7; i++)
	{
		int curXDistance = getBoxX(i) - 11 * brickSize;
		int curBoxCol = curXDistance / brickSize;

		int curYDistance = getBoxY(i) + 50 - 6 * brickSize;
		int curBoxRow = curYDistance / brickSize;

		curBoxCol += 11;
		curBoxRow += 6;

		if (map.firstLevelMap[curBoxRow][curBoxCol] == '.')
		{
			if ((getBoxX(i) > brickSize * curBoxCol + 12) && (getBoxX(i) < brickSize * curBoxCol + 30)) 
			{
				if ((getBoxY(i) < brickSize * curBoxRow + 30) && (getBoxY(i) > brickSize * curBoxRow))
				{
					map.firstLevelMap[curBoxRow][curBoxCol] = 'G';
				}
			}
		}
		//else
		//{
			
			//if (map.firstLevelMap[curBoxRow][curBoxCol] != ' ')
			//{
			//	map.firstLevelMap[curBoxRow][curBoxCol] = '.';
			//}
		//}
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