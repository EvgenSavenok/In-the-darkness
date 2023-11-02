#include "BackgroundObjects.h"

BackgroundObjects::BackgroundObjects()
{
	dieScientistImg.loadFromFile("Images/die_scientist.png");
	dieScientistTexture.loadFromImage(dieScientistImg);
	dieScientistSprite.setTexture(dieScientistTexture);
	dieScientistSprite.setTextureRect(sf::IntRect(0, 0, 42, 60));
	dieScientistSprite.setPosition(getDieScientistX(), getDieScientistY());

	electricityImg.loadFromFile("Images/electricity.png");
	electricityTexture.loadFromImage(electricityImg);
	electricitySprite.setTexture(electricityTexture);
	electricitySprite.setTextureRect(sf::IntRect(0, 0, 60, 90));
	electricitySprite.setPosition(brickSize * 26 + 15, brickSize * 15);
}