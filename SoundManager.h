#pragma once
#include <SFML/Audio.hpp>

class SoundManager 
{
private:
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
    void playWinMelody();
    void playTeleportMoving();
    void playDeathSound();

    sf::Music roar;
    sf::Music openCage;
    sf::Music teleport;
    sf::Music winMelody;
    sf::Music bgMusic1;
    sf::Music bgMusic2;
    sf::Music death;
};