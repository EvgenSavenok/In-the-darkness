#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Players.h"
#include "Enemies.h"
#include "Map.h"
#include "Animations.h"
#include "Boxes.h"

void pressOnKey(sf::RenderWindow& window, sf::Clock& clock, Players& player, Map& map, Animations& animeOfTeleport, Boxes& box, Animations& cage)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed) {
            clock.restart();
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            if (event.key.code == sf::Keyboard::D)
            {
                player.setDir(Direction::right);
                player.move(window, map, animeOfTeleport, box, cage);
            }
            if (event.key.code == sf::Keyboard::A)
            {
                player.setDir(Direction::left);
                player.move(window, map, animeOfTeleport, box, cage);
            }
            if (event.key.code == sf::Keyboard::W)
            {
                player.setDir(Direction::up);
                player.move(window, map, animeOfTeleport, box, cage);
            }
            if (event.key.code == sf::Keyboard::S)
            {
                player.setDir(Direction::down);
                player.move(window, map, animeOfTeleport, box, cage);
            }
        }
    }
}

void updatePlayerState(sf::Clock& playerClock, Players& player, Map& map, Animations& animeOfTeleport, sf::Clock& teleportClock)
{
    if (player.update(playerClock, map, teleportClock, animeOfTeleport))
    {
        teleportClock.restart();
    }
}

void updateBoarState(Enemies& enemyBoar, sf::Clock& enemyClock)
{
    if (enemyBoar.enemyMove(enemyClock))
    {
        enemyClock.restart();
    }
}

int main() 
{
    sf::RenderWindow window;
    window.create(sf::VideoMode::getDesktopMode(), L"Rage");
    window.setMouseCursorVisible(false);
    const float screenWidth = sf::VideoMode::getDesktopMode().width;
    const float screenHeight = sf::VideoMode::getDesktopMode().height;
    Players player;
    Enemies enemyBoar;
    Animations animeOfTeleport;
    Animations cage;
    Boxes box;
    Map map;
    sf::Clock playerClock;
    sf::Clock enemyClock;
    sf::Clock teleportClock;
    sf::Clock cageClock;
    sf::View camera(sf::FloatRect(0, 0, screenWidth, screenHeight));
    while (window.isOpen()) 
    {
        pressOnKey(window, playerClock, player, map, animeOfTeleport, box, cage);
      //  enemyBoar.setDir(enemyDirection::left);
      //  updateBoarState(enemyBoar, enemyClock);
        updatePlayerState(playerClock, player, map, animeOfTeleport, teleportClock);
        window.clear(sf::Color::Black);
        box.checkAllPoints(map);
        map.createMap(window);
        box.drawBox(window);
        player.drawKey(window);
        cage.setCagePos(window, box, map, cageClock);
        camera.setCenter(player.playerX, player.playerY);
        window.draw(map.getTeleportSprite());
        window.draw(player.getSprite());
        window.draw(enemyBoar.getSprite());
        window.setView(camera); 
        window.display();
    }
    return 0;
}