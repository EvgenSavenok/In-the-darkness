#include <SFML/Graphics.hpp>
#include <iostream>

class Player {
public:
    Sprite playerSprite, brickSprite;
    Texture playerTexture, brickTexture;

    void loadSprite();

private:
    void loadSprite() {
        playerTexture.loadFromFile("Images/girl_forward_1");
        playerSprite.setTexture(playerTexture);
    }
};