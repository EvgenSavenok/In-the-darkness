#include "Animations.h"

Animations::Animations()
{
	cageImg.loadFromFile("Images/cage.png");
	cageTexture.loadFromImage(cageImg);
	cageSprite.setTexture(cageTexture);
	cageSprite.setTextureRect(sf::IntRect(0, 0, 90, 90));
}

void Animations::setCagePos(sf::RenderWindow& window, Boxes& box, Map& map, sf::Clock& cageClock)
{
	if (getCageAnimationState())
	{
		map.firstLevelMap[12][31] = ' ';
	}
	else
	{
		cageSprite.setPosition(brickSize * 31, brickSize * 12);
		window.draw(cageSprite);
		startCageAnimation(box, map, window, cageClock);
	}
}

void Animations::startCageAnimation(Boxes& box, Map& map, sf::RenderWindow& window, sf::Clock& cageClock)
{
	#define numOfActivePoints 1
	int countOfPoints = 0;
	for (int i = 0; i < 36; i++)
	{
		for (int j = 0; j < 43; j++)
		{
			if (map.firstLevelMap[i][j] == 'G')
				countOfPoints++;
		}
	}
	if (countOfPoints == numOfActivePoints)
	{
		sf::Time curTime = cageClock.getElapsedTime();
		if (curTime.asSeconds() >= 0.01) 
		{
			setCageHeight(getCageHeight() - 1);
			cageSprite.setTextureRect(sf::IntRect(0, 0, 90, getCageHeight()));
			window.draw(cageSprite);
			if (getCageHeight() == 0)
				setCageAnimationState(true);
			cageClock.restart();
		}
	}
}