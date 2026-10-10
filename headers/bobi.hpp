#pragma once 

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <map>
#include <string>


class Bobi
{
public:
    int imageDelay;
    int screenWidth;
    int screenHeight;
    int chinPadding;
    int speed;
    double dealer;
    SDL_Rect skullHitbox;
    SDL_Rect chestHitbox;
    SDL_Rect chinHitbox;
    int startPos[2];
    std::map<std::string, SDL_Texture*> images;
    std::string imageKey;


    Bobi();
    void draw(SDL_Renderer* renderer);
    void init(int width, int height, SDL_Renderer* renderer);
    void update(int paddX, int paddY);
};