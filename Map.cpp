#include "Map.h"

Map::Map()
{
	wallImg.loadFromFile("Images/tiles.png");
	wallTexture.loadFromImage(wallImg);
	wallSprite.setTexture(wallTexture);
	wallSprite.setTextureRect(sf::IntRect(0, 90, 90, 90));
	wallSprite.setColor(sf::Color(150, 0, 0));

	floorImg.loadFromFile("Images/tiles.png");
	floorTexture.loadFromImage(floorImg);
	floorSprite.setTexture(floorTexture);
	floorSprite.setTextureRect(sf::IntRect(0, 0, 90, 90));

	deviceImg.loadFromFile("Images/tiles.png");
	deviceTexture.loadFromImage(deviceImg);
	deviceSprite.setTexture(deviceTexture);
	deviceSprite.setTextureRect(sf::IntRect(0, 270, 90, 90));

	entranceImg.loadFromFile("Images/entrance.png");
	entranceTexture.loadFromImage(entranceImg);
	entranceSprite.setTexture(entranceTexture);
	entranceSprite.setTextureRect(sf::IntRect(0, 0, 90, 90));

	exitImg.loadFromFile("Images/exit.png");
	exitTexture.loadFromImage(exitImg);
	exitSprite.setTexture(exitTexture);
	exitSprite.setTextureRect(sf::IntRect(0, 0, 90, 104));

	doorImg.loadFromFile("Images/doors.png");
	doorTexture.loadFromImage(doorImg);
	doorSprite.setTexture(doorTexture);
	doorSprite.setTextureRect(sf::IntRect(107, 7, 95, 95));

	teleportImg.loadFromFile("Images/dop_bricks.png");
	teleportTexture.loadFromImage(teleportImg);
	teleportSprite.setTexture(teleportTexture);
	teleportSprite.setTextureRect(sf::IntRect(225, 112, 90, 90));

	boxPointImg.loadFromFile("Images/tiles.png");
	boxPointTexture.loadFromImage(boxPointImg);
	boxPointSprite.setTexture(boxPointTexture);
	boxPointSprite.setTextureRect(sf::IntRect(1, 180, 90, 90));

	greenBoxImg.loadFromFile("Images/green_point.png");
	greenBoxTexture.loadFromImage(greenBoxImg);
	greenBoxSprite.setTexture(greenBoxTexture);
	greenBoxSprite.setTextureRect(sf::IntRect(1, 4, 90, 90));

	iceFloorImg.loadFromFile("Images/ice_floor.png");
	iceFloorTexture.loadFromImage(iceFloorImg);
	iceFloorSprite.setTexture(iceFloorTexture);
	iceFloorSprite.setTextureRect(sf::IntRect(0, 0, 90, 90));

	laveImg.loadFromFile("Images/lave.jpg");
	laveTexture.loadFromImage(laveImg);
	laveSprite.setTexture(laveTexture);
	laveSprite.setTextureRect(sf::IntRect(0, 0, 90, 90));
}

void Map::createMap(sf::RenderWindow& window)
{
	const float screenWidth = sf::VideoMode::getDesktopMode().width;
	const float screenHeight = sf::VideoMode::getDesktopMode().height;
	int numOfCols = int(screenWidth / brickSize);
	int numOfRows = int(screenHeight / brickSize);

	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			switch (firstLevelMap[i][j])
			{
			case 'B':
			{
				wallSprite.setPosition(brickSize * j, brickSize * i);
				window.draw(wallSprite);
				break;
			}
			case ' ':
			case 'C':
			{
				floorSprite.setPosition(brickSize * j, brickSize * i);
				window.draw(floorSprite);
				break;
			}
			case 'E':
			{
				exitSprite.setPosition(brickSize * j, brickSize * i);
				window.draw(exitSprite);
				break;
			}
			case 'R':
			{
				deviceSprite.setPosition(brickSize * j, brickSize * i);
				window.draw(deviceSprite);
				break;
			}
			case 'H':
			{
				entranceSprite.setPosition(brickSize * j, brickSize * i);
				window.draw(entranceSprite);
				break;
			}
			case 'D':
			{
				doorSprite.setPosition(brickSize * j, brickSize * i);
				window.draw(doorSprite);
				break;
			}
			case 'T':
			{
				teleportSprite.setPosition(brickSize * j, brickSize * i);
				window.draw(teleportSprite);
				break;
			}
			case '.':
			{
				boxPointSprite.setPosition(brickSize * j, brickSize * i);
				window.draw(boxPointSprite);
				break;
			}
			case 'G':
			{
				greenBoxSprite.setPosition(brickSize * j, brickSize * i);
				window.draw(greenBoxSprite);
				break;
			}
			case 'I':
			{
				iceFloorSprite.setPosition(brickSize * j, brickSize * i);
				window.draw(iceFloorSprite);
				break;
			}
			case 'L':
			{
				laveSprite.setPosition(brickSize * j, brickSize * i);
				window.draw(laveSprite);
				break;
			}
			}
		}
	}
}