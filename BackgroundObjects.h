#pragma once
#include <SFML/Graphics.hpp>

class BackgroundObjects
{
private:
	int brickSize = 90;

	sf::Image dieScientistImg;
	sf::Texture dieScientistTexture;
	sf::Sprite dieScientistSprite;
	
	sf::Image scullImg;
	sf::Texture scullTexture;
	sf::Sprite scullSprite;

	float dieScientistX = brickSize * 22 + 10, dieScientistY = brickSize * 10 + 10;

public:
	BackgroundObjects();
	sf::Sprite getDieScientistSprite() { return dieScientistSprite; }
	void setDieScientistX(float x) { dieScientistX = x; }
	float getDieScientistX() { return dieScientistX; }
	void setDieScientistY(float y) { dieScientistY = y; }
	float getDieScientistY() { return dieScientistY; }
};