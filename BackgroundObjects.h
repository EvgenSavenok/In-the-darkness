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

	sf::Image electricityImg;
	sf::Texture electricityTexture;
	sf::Sprite electricitySprite;

	sf::Vector2f boxPosition;

public:
	BackgroundObjects();
	sf::Sprite getDieScientistSprite() { return dieScientistSprite; }
	sf::Sprite getElectricitySprite() { return electricitySprite; }
	void setDieScientistX(float x) { dieScientistX = x; }
	float getDieScientistX() { return dieScientistX; }
	void setDieScientistY(float y) { dieScientistY = y; }
	float getDieScientistY() { return dieScientistY; }
	std::vector<sf::Vector2f> electricities;
};

