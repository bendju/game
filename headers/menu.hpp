#pragma once
#include <SDL.h>
#include <map>
#include <SDL_image.h>

class Menu
{
public:
    SDL_Rect skullRect;
    SDL_Rect chestRect;
    bool     playHover;
    int      screenWidth;
    int      screenHeight;
    SDL_Rect playRect;
    SDL_Rect playRectHover;
    SDL_Rect lightRect;
    int      playSize[2];
    int      startX;
    int      startY;
    std::map<std::string, SDL_Texture*> image;
    std::vector<std::vector<int>> map;
    std::map<std::string, SDL_Texture*> tiles;

    Menu();
    void init(SDL_Renderer* renderer, int width, int height);
    void draw(SDL_Renderer* renderer);
    void update();
    void initImages(SDL_Renderer* renderer);
    void mouseEvents(int x, int y);
};