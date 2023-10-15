#pragma once
#include <SFML/Graphics.hpp>

class Map
{
private:
    sf::Image wallImg;
    sf::Texture wallTexture;
    sf::Sprite wallSprite;

    sf::Image floorImg;
    sf::Texture floorTexture;
    sf::Sprite floorSprite;

    sf::Image exitImg;
    sf::Texture exitTexture;
    sf::Sprite exitSprite;

    sf::Image deviceImg;
    sf::Texture deviceTexture;
    sf::Sprite deviceSprite;

    sf::Image entranceImg;
    sf::Texture entranceTexture;
    sf::Sprite entranceSprite;

    sf::Image doorImg;
    sf::Texture doorTexture;
    sf::Sprite doorSprite;

    sf::Image boxPointImg;
    sf::Texture boxPointTexture;
    sf::Sprite boxPointSprite;

    sf::Image greenBoxImg;
    sf::Texture greenBoxTexture;
    sf::Sprite greenBoxSprite;

    int plateX, plateY;

public:
    sf::Sprite getWallSprite() { return wallSprite; };
    sf::Sprite getTeleportSprite() { return teleportSprite; };
    Map();
    void createMap(sf::RenderWindow& window);
    static const int brickSize = 90;
    int getPlateX() { return plateX; }
    int getPlateY() { return plateY; }
    void setPlateX(int plateX) { this->plateX = plateX; }
    void setPlateY(int plateY) { this->plateY = plateY; }

    sf::Image teleportImg;
    sf::Texture teleportTexture;
    sf::Sprite teleportSprite;

    int startXCoordinate, startYCoordinate;

    sf::String firstLevelMap[36] = {
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBHBBBBBBBBBBBBBB   BBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBB BBBB        .    BBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBB BBBBBBBBBBBBBB  .BBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBB BBBB       B.BB  BBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBB BBBBBBBBBB B B . BBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBB TBBBBBBEBBBB  .  . BBBBBBBBBBBBBBB",
        "BBBBBBBBBBBB BBBBB   BBBB   .  CBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBB   D BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBB B BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBB B BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBRB BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBB BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBB    BBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBB BBBBBBBBBB BBBBBBBBBBBBBBBBBBBBBB",     //width = 22
        "BBBBBBBBBBBBB BBBBBBBBBB BBBBBBBBBBBBBBBBBBBBBB",     //height = 24                                                           
        "BBBBBBBBBBBBB            BBBBBBBBBBBBBBBBBBBBBB",     /* B - кирпич; E - дверь выхода */
        "BBBBBBBBBBBBB BBBB BBBBB BBBBBBBBBBBBBBBBBBBBBB",     /* R - кирпич с прибором; D - обычная дверь */
        "BBBBBBBBBBBBB BB         BBBBBBBBBBBBBBBBBBBBBB",     /* H - вход */
        "BBBBBBBBBBBBB BB BBBBBBB BBBBBBBBBBBBBBBBBBBBBB",     /* T - телепорт */
        "BBBBBBBBBBBBBDBB BBBBBBB        BBBBBBBBBBBBBBB",     /*C - клетка*/
        "BBBBBBBBBBB    B BBBBBBBBBBBBBB BBBBBBBBBBBBBBB",     /*. - точка необходимой остановки ящика*/
        "BBBBBBBBBBB    B BBBBBBBBBBBBBB BBBBBBBBBBBBBBB",     /*G - зеленая коробка (уже на нужной точке)*/
        "BBBBBBBBBBB    B          RBBBB BBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBRBBBBBBBBBBBBBBB",
        "BBB BBB BB    BB BBBBB     BBBBBBBBBBBBBBBBBBB",
        "BBB BBB BB BBBBB BBBBB BBB BBBBBBBBBBBBBBBBBBBB",
        "BBB     BB    BB BBBBB     BBBBBBBBBBBBBBBBBBBB",
        "BBB BBB BB BBBBB BBBBB BBBBBBBBBBBBBBBBBBBBBBBB",
        "BBB BBB BB    BB    BB BBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
    };
};