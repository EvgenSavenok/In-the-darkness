#include "Menu.h"

Menu::Menu()
{
	winImg.loadFromFile("Images/winBG.png");
	winTexture.loadFromImage(winImg);
	winSprite.setTexture(winTexture);

	menuBGImg.loadFromFile("Images/menuBG.png");
	menuBGTexture.loadFromImage(menuBGImg);
	menuBGSprite.setTexture(menuBGTexture);

	startTabImg.loadFromFile("Images/startTab.png");
	startTabTexture.loadFromImage(startTabImg);
	startTabSprite.setTexture(startTabTexture);
	
	isMenu = true;
	isWinScreen = false;
}

void Menu::startWin(SoundManager& sound, sf::RenderWindow& window, sf::View& camera)
{
	sf::Event event;
	window.clear(sf::Color::Black);
	sound.bgMusic1.stop();
	sound.bgMusic2.stop();
	camera.setCenter(0, 0);
	if (sound.winMelody.getStatus() != sf::Sound::Playing)
		sound.playWinMelody();
	winSprite.setPosition(camera.getCenter().x - 570, camera.getCenter().y - 500);
	window.draw(winSprite);
	isWinScreen = true;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
			if (event.key.code == sf::Keyboard::Enter)
			{
				isMenu = true;
				sound.winMelody.stop();
				isWinScreen = false;
			}
		}
	}
}

void Menu::showMenu(SoundManager& sound, sf::RenderWindow& window, sf::View& camera, Map& map)
{
	int numOfTab = 0;
	sf::Event event;
	window.clear(sf::Color(129, 181, 221));
	sound.bgMusic1.stop();
	sound.bgMusic2.stop();
	camera.setCenter(0, 0);
	menuBGSprite.setPosition(camera.getCenter().x + 200, camera.getCenter().y);
	if (map.isOnceWin)
	{
		menuBGSprite.setPosition(camera.getCenter().x - 350, camera.getCenter().y - 450);
		startTabSprite.setPosition(camera.getCenter().x - 350 + 150, camera.getCenter().y - 450 + 380);
	}
	startTabSprite.setPosition(menuBGSprite.getPosition().x + 150, menuBGSprite.getPosition().y + 380);
	window.draw(menuBGSprite);
	window.draw(startTabSprite);
	window.setMouseCursorVisible(true);
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
		}
	}
	if (sf::IntRect(menuBGSprite.getPosition().x + 150, menuBGSprite.getPosition().y + 380, 300, 116).contains(sf::Mouse::getPosition(window)) && !map.isOnceWin)
	{ 
		startTabSprite.setColor(sf::Color::Red); 
		numOfTab = 1;
	}
	else if (sf::IntRect(camera.getCenter().x + 380, camera.getCenter().y + 380, 300, 116).contains(sf::Mouse::getPosition(window)))
	{
		float a = camera.getCenter().x;
		startTabSprite.setColor(sf::Color::Red);
		numOfTab = 1;
	}
	else
	{
		startTabSprite.setColor(sf::Color::Black);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (numOfTab == 1)
		{
			window.setMouseCursorVisible(false);
			isMenu = false;
		}
	}
}