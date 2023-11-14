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

    sf::Image iceFloorImg;
    sf::Texture iceFloorTexture;
    sf::Sprite iceFloorSprite;

    sf::Image laveImg;
    sf::Texture laveTexture;
    sf::Sprite laveSprite;

    int plateX = -1, plateY = -1;

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

    bool isOnceWin = false;

    int startXCoordinate, startYCoordinate;

    sf::String firstLevelMap[mapHeight] = {
        "IIIIIIIIIRBBBBBBBBBBBBBBBBBBBBBBBB",
        "IRRRERRRRRBBBBBBBBBBBBBBBBBBBBBBBB",
        "IRIIIIIIIRBBBBBBBBBBBBBBBBB   BBBB",
        "IRIIIIIIIRBBBBBBB        .    BBBB",
        "IRIRRRIIIRBBBBBBB BBB BBBBB  .BBBB",
        "IRIRIIIIIRBBHBBBB BBB BBB.BB  BBBB",
        "IRIRIRIIIRBB BBBB BBB BBB B . BBBB",
        "IRIRLRIIIRBB TBBB B   BBB     . BB",
        "IRIRRRIIID D BBBBBB BBBBB   .  CBB",
        "IRIIIIIIIRBBBB      BBBBBBBBBDBBBB",
        "RRDRRRRRRRBBBBBBBBBBBB      R R BB",
        "BB R RR R    R RRR   RRRR   R R BB",
        "BBDR RR R RRRR RRR RR R         BB",
        "BB R RR R RRRR RRR RR D R R RRRRBB",
        "BB R    D    D RRR    RRR R R R BB",
        "BB R RR R RRRR RRR RRRR   R   R BB",     
        "BB R RR R RRRR RRR R  RRR R R R BB",                                                               
        "BB R RR R    R   D R  R   R R   BB",     /* B - кирпич; E - дверь выхода */
        "BB RRRRRRRRRRRRRRR    R R R RRRRBB",     /* R - кирпич с прибором; D - обычная дверь */
        "BB      R   R         R   R     BB",     /* H - вход */
        "BB RRRR RR RRRRR RRRRRRRRRR RR RBB",     /* T - телепорт */
        "BB R                   R    RR  BB",     /*C - клетка*/
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",     /*. - точка необходимой остановки ящика*/
        "BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB"      /*G - зеленая коробка (уже на нужной точке)*/
    };                                            /*L - лава*/
};