#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <map>
#include <string>


class Player 
{

public:
    int playerSize;
    int screenWidth;
    int screenHeight;
    SDL_Texture* light;
    int imageCounter;
    int imageDelay;
    std::string imageKey;
    std::string collectedItem;
    std::map<std::string, std::vector<SDL_Texture*>> images;

    Player();
    void draw(SDL_Renderer* renderer);
    void update();
    void init(int width, int height, SDL_Renderer* renderer);
    void initImages(SDL_Renderer* renderer);
    void loadImage(std::string type, SDL_Renderer* renderer);
    void setDirection();
    SDL_Rect playerImage;
    SDL_Rect hitbox;
};