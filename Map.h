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

    static const int mapHeight = 24;
    static const int mapWidth = 43;

    int startXCoordinate, startYCoordinate;

    sf::String firstLevelMap[mapHeight] = {
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBB   BBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBBB        .    BBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBBB BBBBBBBBB  .BBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBHBBBB BBBBBBB.BB  BBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBB BBBB BBBBBBB B . BBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBB TBBB BBBBBBB  .  . BBBBBBBBBBBBBBB",
        "BBBBBBBBBBBB BBBBBBBEBBBB   .  CBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBDBBBBB   BBBBBBBBDBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBB  BBBBBBBB          BBBBBBBBBBBBBBB",
        "BBBBBBBBBBBB  B                 BBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBB R                 BBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBDB                 BBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBB B                 BBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBB B                 BBBBBBBBBBBBBBB",     //width = 22
        "BBBBBBBBBBBBB B                 BBBBBBBBBBBBBBB",     //height = 24                                                           
        "BBBBBBBBBBBBB B                 BBBBBBBBBBBBBBB",     /* B - кирпич; E - дверь выхода */
        "BBBBBBBBBBBBB B                 BBBBBBBBBBBBBBB",     /* R - кирпич с прибором; D - обычная дверь */
        "BBBBBBBBBBBBB B                 BBBBBBBBBBBBBBB",     /* H - вход */
        "BBBBBBBBBBBBB BB BBBBBBB BBBBBBBBBBBBBBBBBBBBBB",     /* T - телепорт */
        "BBBBBBBBBBBBBDBB BBBBBBB        BBBBBBBBBBBBBBB",     /*C - клетка*/
        "BBBBBBBBBBB    B BBBBBBBBBBBBBB BBBBBBBBBBBBBBB",     /*. - точка необходимой остановки ящика*/
        "BBBBBBBBBBB    B BBBBBBBBBBBBBB BBBBBBBBBBBBBBB"      /*G - зеленая коробка (уже на нужной точке)*/
    };
};