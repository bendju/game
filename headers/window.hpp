#pragma once
#include <SDL.h>
#include <functional>
#include <string>
#include "map.hpp"
#include "player.hpp"
#include "menu.hpp"
#include <SDL_image.h>
#include <SDL_mixer.h>

struct Context
{
    SDL_Window   *window;
    SDL_Renderer *renderer;
    SDL_Surface  *surface;
};

class Window
{
public:
    SDL_Event    event;
    int          WIDTH;
    int          HEIGHT;
    Context      context;
    Map          map;
    bool         isStop;
    bool         isGame;
    std::string  hoverState;
    Menu         menu;

    std::map<std::string, SDL_Rect>     rects;
    std::map<std::string, SDL_Texture*> images;

    Window();
    void gameLoop();
    void update();
    void draw();
    void createMap();
    void initImages();
    void initImageRects();
};

