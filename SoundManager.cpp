#include "SoundManager.h"

SoundManager::SoundManager()
{
	bgMusic1.openFromFile("Sounds/bgMusic1.ogg");
	bgMusic1.setVolume(40);
	bgMusic2.openFromFile("Sounds/bgMusic2.ogg");
	bgMusic2.setVolume(20);
	openDoor.openFromFile("Sounds/openDoor.ogg");
	openDoor.setVolume(70);
	beatPlayer.openFromFile("Sounds/beat.ogg");
	beatPlayer.setVolume(50);
	roar.openFromFile("Sounds/roar.ogg");
	roar.setVolume(20);
	takeKey.openFromFile("Sounds/takeKey.ogg");
	takeKey.setVolume(50);
	openCage.openFromFile("Sounds/openCage.ogg");
	openCage.setVolume(30);
	teleport.openFromFile("Sounds/teleport.ogg");
	teleport.setVolume(30);
	winMelody.openFromFile("Sounds/holyMelody.ogg");
	winMelody.setVolume(50);
	death.openFromFile("Sounds/death.ogg");
	death.setVolume(50);
	powerdown.openFromFile("Sounds/powerdown.ogg");
	death.setVolume(50);
}

void SoundManager::playBgMusic()
{
	if (!(bgMusic2.getStatus() == sf::Sound::Playing) && (bgMusic1.getStatus() == sf::Sound::Stopped))
	{
		bgMusic2.stop();
		bgMusic1.play();
	}
	if (!(bgMusic1.getStatus() == sf::Sound::Playing) && (bgMusic2.getStatus() == sf::Sound::Stopped))
	{
		bgMusic1.stop();
		bgMusic2.play();
	}
}

void SoundManager::playOpeningOfDoor()
{
	openDoor.play();
}

void SoundManager::playBeatingOfPlayer()
{
	beatPlayer.play();
}

void SoundManager::playRoar()
{
	roar.play();
}

void SoundManager::playTakingKey()
{
	takeKey.play();
}

void SoundManager::playOpeningOfCage()
{
	openCage.play();
}

void SoundManager::playTeleportMoving()
{
	teleport.play();
}

void SoundManager::playWinMelody()
{
	winMelody.play();
}

void SoundManager::playDeathSound()
{
	death.play();
}

void SoundManager::playPowerdownSound()
{
	powerdown.play();
}