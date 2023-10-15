#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Players.h"
#include "Enemies.h"
#include "Map.h"
#include "Animations.h"
#include "Boxes.h"

int main() 
{
    sf::RenderWindow window;
    window.create(sf::VideoMode::getDesktopMode(), L"Лабиринт");
    window.setMouseCursorVisible(false);
    const float screenWidth = sf::VideoMode::getDesktopMode().width;
    const float screenHeight = sf::VideoMode::getDesktopMode().height;
    Players player;
    Enemies enemy_boar;
    Animations animeOfTeleport;
    Animations cage;
    Boxes box;
    Map map;
    sf::Clock clock;
    sf::Clock enemyClock;
    sf::Clock teleportClock;
    sf::View camera(sf::FloatRect(0, 0, screenWidth, screenHeight));
    while (window.isOpen()) 
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
                    player.move(window, map, animeOfTeleport, box);
                }
                if (event.key.code == sf::Keyboard::A) 
                {
                    player.setDir(Direction::left); 
                    player.move(window, map, animeOfTeleport, box);
                }
                if (event.key.code == sf::Keyboard::W) 
                {
                    player.setDir(Direction::up); 
                    player.move(window, map, animeOfTeleport, box);
                }
                if (event.key.code == sf::Keyboard::S) 
                {
                    player.setDir(Direction::down);    
                    player.move(window, map, animeOfTeleport, box);
                }
            }
        }
        enemy_boar.setDir(enemyDirection::left);
        if (enemy_boar.enemyMove(enemyClock))
        {
            enemyClock.restart();
        }
        if (player.update(clock, map, teleportClock, animeOfTeleport))
        {
            teleportClock.restart();
        }
        window.clear(sf::Color::Black);
        box.checkAllPoints(map);
        map.createMap(window);
        box.drawBox(window);
        player.drawKey(window);
        cage.setCagePos(window, box, map);
        camera.setCenter(player.x, player.y);
        window.draw(map.getTeleportSprite());
        window.draw(player.getSprite());
        window.draw(enemy_boar.getSprite());
        window.setView(camera); 
        window.display();
    }
    return 0;
}