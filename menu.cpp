#include "headers/menu.hpp"
#include <iostream>


Menu::Menu()
{
    startX = 0;
}

void Menu::init(SDL_Renderer* renderer, int width, int height)
{
    playHover    = false;
    screenWidth  = width;
    screenHeight = height;
    initImages(renderer);
    lightRect = {0,0, width, height};

    playSize[0] = 37 * 5;
    playSize[1] = 15 * 5;

    playRect.x  = width / 2 - playSize[0] / 2;
    playRect.y  = height - height / 4 - playSize[1];
    playRect.w  = playSize[0];
    playRect.h  = playSize[1];

    map =
    {
        {0,0,  0  ,0  ,301,107,107,107,107,304,0,0,0,0,0},
        {0,0,  301,107,111,122,171,170,123,110,304,0,0,0,0},
        {0,301,111,121,121,5,5,5,5,121,110,304,0,0,0},
        {0,108,121,5  ,5,5,5,4,5,5,121,110,304,0,0},
        {0,111,5  ,5  ,3,5,5,5,5,5,5,121,102,0,0},
        {0,121,5  ,5  ,5,5,5,5,5,5,0,5,0,0,0},
        {0,0  ,0  ,8  ,5,0,5,5,0,5,0,0,0,0,0},
        {0,0  ,0  ,0  ,5,0,0,5,0,0,0,0,0,0,0},
        {0,0  ,0  ,0  ,0,0,0,0,0,0,0,0,0,0,0},
        {0,0  ,0  ,0  ,0,0,0,0,0,0,0,0,0,0,0},
    };

    startX = (width - map[0].size() * 64) / 2;
}


void Menu::draw(SDL_Renderer* renderer)
{

    for (int i = 0; i< map.size();i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            SDL_Rect rect = {(j + 1) * 64 + startX, i * 64 + 100, 64, 64};
            SDL_RenderCopy(renderer, tiles[std::to_string(map[i][j])], NULL, &rect);
        }
    }

    SDL_RenderCopy(renderer, image["light"], NULL, &lightRect);
    SDL_RenderCopy(renderer, image["play"], NULL, &playRect);
    if (playHover)
    {
        SDL_SetRenderDrawColor(renderer, 255,0,0,255);
        SDL_RenderDrawLine(
            renderer, 
            playRect.x + 5, 
            playRect.y + playRect.h + 5, 
            playRect.x + playRect.w - 27, 
            playRect.y + playRect.h + 5
        );
    }
}

void Menu::update()
{

}

void Menu::initImages(SDL_Renderer* renderer)
{
    image["light"] = IMG_LoadTexture(renderer, "img/light.png");
    image["play"] = IMG_LoadTexture(renderer, "img/menu/play.png");

    int tile[] = {301, 107, 304, 111, 122, 171, 170, 123, 110, 121, 5, 4, 3, 108, 102, 8, -4};
    for (int i = 0; tile[i] != -4; i++)
    {
        std::string key = std::to_string(tile[i]);
        std::string fullpath = "img/" + key + ".png";
        tiles[key] = IMG_LoadTexture(renderer, fullpath.c_str());
    }

    image["skull"] = IMG_LoadTexture(renderer, "img/bobi/skull.png");
    chestRect = {screenWidth / 2 - 33, 255, 66, 50};

    image["chest"] = IMG_LoadTexture(renderer, "img/bobi/chest.png");
    skullRect = {screenWidth / 2 - 27, 200, 54, 57};

}

void Menu::mouseEvents(int x, int y)
{
    SDL_Point p = {x, y};

    if(SDL_PointInRect(&p, &playRect))
    {
        playHover = true;
    }
    else
    {
        playHover = false;
    }
}

