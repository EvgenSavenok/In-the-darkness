#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemies.h"
#include "Map.h"
#include "Animations.h"
#include "Boxes.h"
#include "BackgroundObjects.h"
#include "SoundManager.h"
#include "Menu.h"

void pressOnKey(sf::RenderWindow& window, sf::Clock& clock, Player& player, Map& map, Animations& anime, Boxes& box, Animations& cage, SoundManager& sound, Menu& menu)
{
    sf::Event event;
    bool isTime = false;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) 
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            if (event.key.code == sf::Keyboard::D)
            {
                player.setDir(Direction::right);
                isTime = player.move(window, map, anime, box, cage, clock, sound);
            }
            if (event.key.code == sf::Keyboard::A)
            {
                player.setDir(Direction::left);
                isTime = player.move(window, map, anime, box, cage, clock, sound);
            }
            if (event.key.code == sf::Keyboard::W)
            {
                player.setDir(Direction::up);
                isTime = player.move(window, map, anime, box, cage, clock, sound);
            }
            if (event.key.code == sf::Keyboard::S)
            {
                player.setDir(Direction::down);
                isTime = player.move(window, map, anime, box, cage, clock, sound);
            }
            if (event.key.code == sf::Keyboard::Enter)
            {
                player.resetGame(map, anime, box, sound);
            }
            if ((event.key.code == sf::Keyboard::Enter) && player.getGameOverState())
            {
                player.resetGame(map, anime, box, sound);
            }
        }
        if (isTime)
        {
            clock.restart();
        }
    }
}

void updatePlayerState(sf::Clock& playerClock, Player& player, Map& map, Animations& animeOfTeleport, sf::Clock& teleportClock, sf::RenderWindow& window, sf::View& camera, SoundManager& sound)
{
    if (player.update(playerClock, map, teleportClock, animeOfTeleport, window, camera, sound))
    {
        teleportClock.restart();
    }
}

void updateMapState(Map& map, sf::RenderWindow& window, Animations& anime, sf::Clock& leftDoorClock, sf::Clock& rightDoorClock)
{
    anime.checkOnOpenDoor(map, window, leftDoorClock, rightDoorClock);
}

void updateBoarState(Enemies& enemyBoar, sf::Clock& enemyClock, Player& player, SoundManager& sound)
{
    if (enemyBoar.enemyMove(enemyClock, player, sound))
    {
        enemyClock.restart();
    }
    enemyDirection dir = enemyBoar.getDir();
    enemyBoar.setDir(dir);
}

int main() 
{
    sf::RenderWindow window;
    window.create(sf::VideoMode::getDesktopMode(), L"In the darkness", sf::Style::Fullscreen);
    const float screenWidth = sf::VideoMode::getDesktopMode().width;
    const float screenHeight = sf::VideoMode::getDesktopMode().height;
    Player player;
    Enemies enemyBoar1(18, 12);
    Enemies enemyBoar2(4, 14);
    Enemies enemyBoar3(25, 15);
    Enemies enemyBoar4(21, 16);
    Enemies enemyBoar5(2, 20);
    Map map;
    Animations anime;
    Animations cage;
    Boxes box;
    Menu menu;
    BackgroundObjects backgroundObject;
    sf::Clock playerClock;
    sf::Clock enemyClock1;
    sf::Clock enemyClock2;
    sf::Clock enemyClock3;
    sf::Clock enemyClock4;
    sf::Clock enemyClock5;
    sf::Clock teleportClock;
    sf::Clock cageClock;
    sf::Clock leftDoorClock;
    sf::Clock rightDoorClock;
    sf::View camera(sf::FloatRect(0, 0, screenWidth, screenHeight));
    sf::Texture fogTexture;
    SoundManager sound;
    fogTexture.loadFromFile("Images/fog.png");
    sf::Sprite fogSprite(fogTexture);
    fogSprite.setScale(2.2, 2.2);
    while (window.isOpen()) 
    {
        if (menu.isMenu)
        {
            menu.showMenu(sound, window, camera, map);
        }
        if (!player.isGameWin && !menu.isMenu && !menu.isWinScreen)
        {
            sound.playBgMusic();
            pressOnKey(window, playerClock, player, map, anime, box, cage, sound, menu);
            updateBoarState(enemyBoar1, enemyClock1, player, sound);
            updateBoarState(enemyBoar2, enemyClock2, player, sound);
            updateBoarState(enemyBoar3, enemyClock3, player, sound);
            updateBoarState(enemyBoar4, enemyClock4, player, sound);
            updateBoarState(enemyBoar5, enemyClock5, player, sound);
            updatePlayerState(playerClock, player, map, anime, teleportClock, window, camera, sound);
            window.clear(sf::Color::Black);
            box.checkAllPoints(map);
            map.createMap(window);
            updateMapState(map, window, anime, leftDoorClock, rightDoorClock);
            box.drawBox(window);
            player.drawKey(window);
            cage.setCagePos(window, box, map, cageClock, sound, anime);
            camera.setCenter(player.playerX, player.playerY);
            window.draw(map.getTeleportSprite());
            window.draw(backgroundObject.getDieScientistSprite());
            window.setView(camera);
            fogSprite.setPosition(player.playerX - 1240, player.playerY - 1200);
            window.draw(enemyBoar1.getSprite());
            window.draw(enemyBoar2.getSprite());
            window.draw(enemyBoar3.getSprite());
            window.draw(enemyBoar4.getSprite());
            window.draw(enemyBoar5.getSprite());
           // window.draw(fogSprite);
            window.draw(player.getLifeBarSprite());
            window.draw(player.getSprite());
            player.checkOnGameOver(camera, window);
        }
        else if (!menu.isMenu)
        {
            player.resetGame(map, anime, box, sound);
            menu.startWin(sound, window, camera);
        }
        window.display();
    }
    return 0;
}