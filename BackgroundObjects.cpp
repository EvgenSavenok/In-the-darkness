#include "BackgroundObjects.h"

BackgroundObjects::BackgroundObjects()
{
	dieScientistImg.loadFromFile("Images/die_scientist.png");
	dieScientistTexture.loadFromImage(dieScientistImg);
	dieScientistSprite.setTexture(dieScientistTexture);
	dieScientistSprite.setTextureRect(sf::IntRect(0, 0, 42, 60));
	dieScientistSprite.setPosition(getDieScientistX(), getDieScientistY());
}