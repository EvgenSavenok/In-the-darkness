#pragma once
#include <SFML/Graphics.hpp>

class BackgroundObjects
{
private:
	int brickSize = 90;

	sf::Image dieScientistImg;
	sf::Texture dieScientistTexture;
	sf::Sprite dieScientistSprite;
	float dieScientistX = brickSize * 27, dieScientistY = brickSize * 14 + 10;

public:
	BackgroundObjects();
	sf::Sprite getDieScientistSprite() { return dieScientistSprite; }
	void setDieScientistX(float x) { dieScientistX = x; }
	float getDieScientistX() { return dieScientistX; }
	void setDieScientistY(float y) { dieScientistY = y; }
	float getDieScientistY() { return dieScientistY; }
};
