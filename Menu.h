#pragma once
#include <SFML/Graphics.hpp>
#include "SoundManager.h"
#include "Process.h"
#include "Map.h"

class Menu
{
private:
	sf::Image winImg;
	sf::Texture winTexture;
	sf::Sprite winSprite;

	sf::Image startTabImg;
	sf::Texture startTabTexture;
	sf::Sprite startTabSprite;

	sf::Image menuBGImg;
	sf::Texture menuBGTexture;
	sf::Sprite menuBGSprite;

public:
	Menu();
	void startWin(SoundManager& sound, sf::RenderWindow& window, sf::View& camera);
	void showMenu(SoundManager& sound, sf::RenderWindow& window, sf::View& camera, Map& map);
	bool isMenu;
	bool isWinScreen;
};