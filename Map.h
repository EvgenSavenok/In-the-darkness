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
    static const int mapWidth = 34;

    int startXCoordinate, startYCoordinate;

    sf::String firstLevelMap[mapHeight] = {
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
        "BBBBBBBBBBBBBBBBBBBBBBBBBBB   BBBB",
        "BBBBBBBBBBBBBBBBB        .    BBBB",
        "BBBBBBBBBBBBBBBBB BBBBBBBBB  .BBBB",
        "BBBBBBBBBBBBHBBBB BBBBBBB.BB  BBBB",
        "BBBBBBBBBBBB BBBB BBBBBBB B . BBBB",
        "BBBBBBBBBBBB TBBB BBBBBBB  .  . BB",
        "BBBBBBBBBBBB BBBBBBBEBBBB   .  CBB",
        "BBBBBBBBBBBBDBBBBB   BBBBBBBBDBBBB",
        "BBBBBBBBBBBB  BBBBBBBB      R R BB",
        "BBBBBBBBBBBB  B       RRRR  R R BB",
        "BBBBBBBBBBBBB B    RR R         BB",
        "BBBBBBBBBBBBB B    RR   R R RRRRBB",
        "BBBBBBBBBBBBB B       RRR R R R BB",
        "BBBBBBBBBBBBB B       R   R   R BB",     
        "BBBBBBBBBBBBB B       RRR R R R BB",                                                               
        "BBBBBBBBBBBBB B       R   R R   BB",     /* B - кирпич; E - дверь выхода */
        "BBBBBBBBBBBBB B       R R R RRRRBB",     /* R - кирпич с прибором; D - обычная дверь */
        "BBBBBBBBBBBBB B       R   R     BB",     /* H - вход */
        "BBBBBBBBBBBBBDRR RRRRRRRRRR RR RBB",     /* T - телепорт */
        "BBBBBBBBBBBBB    RRRRRRR    RR  BB",     /*C - клетка*/
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",     /*. - точка необходимой остановки ящика*/
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"      /*G - зеленая коробка (уже на нужной точке)*/
    };
};