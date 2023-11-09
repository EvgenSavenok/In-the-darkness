#include <SFML/Audio.hpp>

class SoundManager {
public:
    sf::SoundBuffer buf;
    sf::Sound step;

    SoundManager() {
        buf.loadFromFile("Sounds/step.mp3");
        step.setBuffer(buf);
    }
};