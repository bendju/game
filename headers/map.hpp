#pragma once 

#include <SDL.h>
#include <vector>
#include <map>
#include <SDL_image.h>
#include "bobi.hpp"
#include "player.hpp"
#include <SDL_ttf.h>

struct Vec2
{
    int x;
    int y;
};

class Map
{
public:
    Player player;
    Bobi bobi;
    bool vibrateLeft;
    bool* isGameP;
    bool gameOver;
    int startPos[2];
    int startDraw[2];
    int speed;
    int gridSize;
    int playerSize;
    int screenWidth;
    int screenHeight;
    std::vector<std::vector<int>>       map;
    std::map<std::string, SDL_Texture*> tiles;
    SDL_Texture* light;
    SDL_Texture* narrow_light;
    SDL_Texture* gameOverImg;
    SDL_Rect gameOverRect;

    SDL_Texture* continueImg;
    SDL_Rect continueRect;

    std::string collectedItem;
    bool saw;
    int keyCounter;

    Map();
    void update();
    void draw(SDL_Renderer* renderer);
    void checkMoving();
    void pickUpItem();
    Vec2 direction();
    void move(Vec2 dir);
    void init(int width, int height, SDL_Renderer* renderer, bool* isGame);
    void initTiles(SDL_Renderer* renderer);
    void initMap();
    void finish();
    void vibration();
};