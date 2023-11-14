#pragma once
#include <SFML/Audio.hpp>

class SoundManager 
{
private:
    sf::Music openDoor;
    sf::Music beatPlayer;
    sf::Music takeKey;
    sf::Music powerdown;
    bool isPlayPowerdown = true;

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
    void playPowerdownSound();

    sf::Music roar;
    sf::Music openCage;
    sf::Music teleport;
    sf::Music winMelody;
    sf::Music bgMusic1;
    sf::Music bgMusic2;
    sf::Music death;

    bool getPowerdownSound() { return isPlayPowerdown; };
    void setPowerDownSound(bool isPlayPowerDown) { this->isPlayPowerdown = isPlayPowerDown; };
};