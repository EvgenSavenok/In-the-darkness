#pragma once
#include <SFML/Audio.hpp>

class SoundManager 
{
private:
    sf::Music bgMusic1;
    sf::Music bgMusic2;
    sf::Music openDoor;
    sf::Music beatPlayer;
    sf::Music takeKey;

public:
    SoundManager();
    void playBgMusic();
    void playOpeningOfDoor();
    void playBeatingOfPlayer();
    void playRoar();
    void playTakingKey();
    void playOpeningOfCage();
    void playGreenBoxSound();
    void playTeleportMoving();

    sf::Music roar;
    sf::Music openCage;
    sf::Music teleport;
};