#pragma once
#include <SFML/Graphics.hpp>
#include "Map.h"

class Boxes
{
private:
	float boxX;
	float boxY;

	sf::Image boxImg;
	sf::Texture boxTexture;
	sf::Sprite boxSprite;

	float brickSize = 90;
	const float offset = 4;
	bool isBoxOnPoint[7];

public:
	sf::Vector2f position;
	Boxes();

	bool getBoxPoint(int indexOfPoint) { return isBoxOnPoint[indexOfPoint]; }
	void setBoxPoint(bool point, int indexOfPoint) { this->isBoxOnPoint[indexOfPoint] = point; }
	float getBoxX(int indexOfBox) { return boxes[indexOfBox].x; }
	void setBoxX(float boxX, int indexOfBox) { this->boxes[indexOfBox].x = boxX; }
	float getBoxY(int indexOfBox) { return boxes[indexOfBox].y; }
	void setBoxY(float boxY, int indexOfBox) { this->boxes[indexOfBox].y = boxY; }

	void drawBox(sf::RenderWindow& window);
	void pushBox(int curRow, int curCol, char dir, Boxes& box, int indexOfBox);
	void checkAllPoints(Map& map);
	void initializeBoxes();
	std::vector<sf::Vector2f> boxes;
};

