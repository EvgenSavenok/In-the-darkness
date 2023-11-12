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
}

void Menu::startWin(SoundManager& sound, sf::RenderWindow& window)
{
	sf::Event event;
	window.clear(sf::Color::Black);
	sound.bgMusic1.stop();
	sound.bgMusic2.stop();
	if (sound.winMelody.getStatus() != sf::Sound::Playing)
		sound.playWinMelody();
	winSprite.setPosition(-550, -500);
	window.draw(winSprite);
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
			}
		}
	}
}

void Menu::showMenu(SoundManager& sound, sf::RenderWindow& window, sf::View& camera)
{
	int numOfTab = 0;
	sf::Event event;
	window.clear(sf::Color(129, 181, 221));
	sound.bgMusic1.stop();
	sound.bgMusic2.stop();
	startTabSprite.setPosition(camera.getCenter().x - 600, camera.getCenter().y - 200);
	menuBGSprite.setPosition(camera.getCenter().x - 750, camera.getCenter().y - 550);
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
	if (sf::IntRect(camera.getCenter().x - 600, camera.getCenter().y - 200, 300, 116).contains(sf::Mouse::getPosition(window)))
	{ 
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