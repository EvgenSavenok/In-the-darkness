#include "Animations.h"

Animations::Animations()
{
	cageImg.loadFromFile("Images/cage.png");
	cageTexture.loadFromImage(cageImg);
	cageSprite.setTexture(cageTexture);
	cageSprite.setTextureRect(sf::IntRect(0, 0, 90, 90));
}

void Animations::setCagePos(sf::RenderWindow& window, Boxes& box, Map& map)
{
	cageSprite.setPosition(brickSize * 31, brickSize * 12);
	window.draw(cageSprite);
	startCageAnimation(box, map);
}

void Animations::startCageAnimation(Boxes& box, Map& map)
{
	int countOfPoints = 0;
	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 43; j++)
		{
			if (map.firstLevelMap[i][j] == 'G')
				countOfPoints++;
		}
	}
	if (countOfPoints == 7)
	{
		countOfPoints = 7;
	}
}