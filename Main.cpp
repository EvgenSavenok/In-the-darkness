#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Players.h"
#include "Enemies.h"
#include "Map.h"
#include "Animations.h"
#include "Boxes.h"
#include <Candle/RadialLight.hpp>
#include <Candle/LightingArea.hpp>
#include "LightSource.hpp"
#include "BackgroundObjects.h"

void pressOnKey(sf::RenderWindow& window, sf::Clock& clock, Player& player, Map& map, Animations& anime, Boxes& box, Animations& cage)
{
    sf::Event event;
    bool isTime = false;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            if (event.key.code == sf::Keyboard::D)
            {
                player.setDir(Direction::right);
                isTime = player.move(window, map, anime, box, cage, clock);
            }
            if (event.key.code == sf::Keyboard::A)
            {
                player.setDir(Direction::left);
                isTime = player.move(window, map, anime, box, cage, clock);
            }
            if (event.key.code == sf::Keyboard::W)
            {
                player.setDir(Direction::up);
                isTime = player.move(window, map, anime, box, cage, clock);
            }
            if (event.key.code == sf::Keyboard::S)
            {
                player.setDir(Direction::down);
                isTime = player.move(window, map, anime, box, cage, clock);
            }
        }
        if (isTime)
        {
            clock.restart();
        }
    }
}

void updatePlayerState(sf::Clock& playerClock, Player& player, Map& map, Animations& animeOfTeleport, sf::Clock& teleportClock)
{
    if (player.update(playerClock, map, teleportClock, animeOfTeleport))
    {
        teleportClock.restart();
    }
}

void updateMapState(Map& map, sf::RenderWindow& window, Animations& anime, sf::Clock& leftDoorClock, sf::Clock& rightDoorClock)
{
    anime.checkOnOpenDoor(map, window, leftDoorClock, rightDoorClock);
}

void updateBoarState(Enemies& enemyBoar, sf::Clock& enemyClock, Player player)
{
    if (enemyBoar.enemyMove(enemyClock, player))
    {
        enemyClock.restart();
    }
    enemyDirection dir = enemyBoar.getDir();
    enemyBoar.setDir(dir);
}

int main() 
{
    sf::RenderWindow window;
    window.create(sf::VideoMode::getDesktopMode(), L"In the darkness");
    window.setMouseCursorVisible(false);
    const float screenWidth = sf::VideoMode::getDesktopMode().width;
    const float screenHeight = sf::VideoMode::getDesktopMode().height;
    Player player;
    Enemies enemyBoar;
    Map map;
    Animations anime;
    Animations cage;
    Boxes box;
    BackgroundObjects backgroundObject;
    sf::Clock playerClock;
    sf::Clock enemyClock;
    sf::Clock teleportClock;
    sf::Clock cageClock;
    sf::Clock leftDoorClock;
    sf::Clock rightDoorClock;
    sf::View camera(sf::FloatRect(0, 0, screenWidth, screenHeight));
    sf::Texture fogTexture;
    fogTexture.loadFromFile("Images/fog.png");
    sf::Sprite fogSprite(fogTexture);
    fogSprite.setScale(2.2, 2.2);
    while (window.isOpen()) 
    {
        pressOnKey(window, playerClock, player, map, anime, box, cage);
        updateBoarState(enemyBoar, enemyClock, player);
        updatePlayerState(playerClock, player, map, anime, teleportClock);
        window.clear(sf::Color::Black);
        box.checkAllPoints(map);
        map.createMap(window);
        updateMapState(map, window, anime, leftDoorClock, rightDoorClock);
        box.drawBox(window);
        player.drawKey(window);
        cage.setCagePos(window, box, map, cageClock);
        camera.setCenter(player.playerX, player.playerY);
        window.draw(map.getTeleportSprite());
        window.draw(backgroundObject.getDieScientistSprite());
        window.setView(camera); 
        fogSprite.setPosition(player.playerX - 1240, player.playerY - 1200);
       // window.draw(fogSprite);
        window.draw(player.getSprite());
        window.draw(enemyBoar.getSprite());
        window.display();
    }
    return 0;
}