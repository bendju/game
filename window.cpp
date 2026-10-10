#include <iostream>
#include "headers/window.hpp"
#include "headers/tileMap.hpp"

Window::Window()
{
    hoverState = "none";
    isStop     = false;
    isGame     = false;
    WIDTH      = 800;
    HEIGHT     = 500;
    

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) 
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
        exit(3);
    }
    

    context.window = SDL_CreateWindow(
        "Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH,
        HEIGHT,
        SDL_WINDOW_FULLSCREEN
    );

    context.renderer = SDL_CreateRenderer(
        context.window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    SDL_SetWindowFullscreen(context.window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    SDL_GetWindowSize(context.window, &WIDTH, &HEIGHT);
    SDL_SetRenderDrawBlendMode(context.renderer, SDL_BLENDMODE_BLEND);
    
    map.init(WIDTH, HEIGHT, context.renderer, &isGame);
    menu.init(context.renderer, WIDTH, HEIGHT);

    initImages();
    initImageRects();

    if (Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG) == 0) {
        std::cout << "Mix_Init hiba: " << Mix_GetError() << std::endl;
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cout << "Mix_OpenAudio hiba: " << Mix_GetError() << std::endl;
        return;
    }

    // TODO: add music elements
    Mix_Music* music = Mix_LoadMUS("music/bg.mp3");
    if (music == nullptr) {
        std::cout << "Mix_LoadMUS hiba: " << Mix_GetError() << std::endl;
        return;
    }

    if (Mix_PlayMusic(music, 0) < 0) {
        std::cout << "Mix_PlayMusic hiba: " << Mix_GetError() << std::endl;
    }
}

void Window::gameLoop()
{

    bool running = true;
    while (running)
    {

        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE && isGame && !map.gameOver)
                {
                    isStop = !isStop;
                }
                if (map.gameOver && event.key.keysym.scancode == SDL_SCANCODE_SPACE)
                {
                    createMap();
                    map.gameOver = false;
                }
            }
            if (event.type == SDL_QUIT) 
            {
                running = false;
                break;
            }


            if(event.type == SDL_MOUSEBUTTONDOWN)
            {
                SDL_Point p = {event.button.x, event.button.y};
                if(SDL_PointInRect(&p, &menu.playRect) && !isGame)
                {
                    createMap();
                    isGame = true;
                }

                if (isStop && isGame)
                {
                    if(SDL_PointInRect(&p, &rects["continue"]))
                    {
                        isStop = false;
                    }
                    if(SDL_PointInRect(&p, &rects["mainMenu"]))
                    {

                        isGame = false;
                        isStop = false;
                    }
                    if(SDL_PointInRect(&p, &rects["restart"]))
                    {
                        createMap();
                        isStop = false;
                    }
                }
            }

            if(event.type == SDL_MOUSEMOTION)
            {
                menu.mouseEvents(event.motion.x, event.motion.y);
                SDL_Point p = {event.motion.x, event.motion.y};

                if (isStop && isGame)
                {
                    if(SDL_PointInRect(&p, &rects["continue"]))
                    {
                        hoverState = "continue";
                    }
                    else if (SDL_PointInRect(&p, &rects["mainMenu"]))
                    {
                        hoverState = "mainMenu";
                    }
                    else if (SDL_PointInRect(&p, &rects["restart"]))
                    {
                        hoverState = "restart";
                    }
                    else 
                    {
                        hoverState = "none";
                    }
                }
            }
        }


        SDL_SetRenderDrawColor(context.renderer, 0, 0, 0, 255);
        SDL_RenderClear(context.renderer);

        draw();

        if (!isStop)
        {
            update();
        }
        SDL_RenderPresent(context.renderer);
        
    }

    SDL_DestroyRenderer(context.renderer);
    SDL_DestroyWindow(context.window);

    SDL_Quit();

}

void Window::draw()
{
    if (isGame)
    {
        map.draw(context.renderer);
        

        if (isStop)
        {
            SDL_Rect blur = {0,0, WIDTH, HEIGHT};
            SDL_SetRenderDrawColor(context.renderer, 0, 0, 0, 200);
            SDL_RenderFillRect(context.renderer, &blur);

            SDL_RenderCopy(context.renderer, images["menuText"], NULL, &rects["menu"]);
            SDL_RenderCopy(context.renderer, images["continue"], NULL, &rects["continue"]);
            SDL_RenderCopy(context.renderer, images["mainMenu"], NULL, &rects["mainMenu"]);
            SDL_RenderCopy(context.renderer, images["restart"], NULL, &rects["restart"]);

            if (hoverState == "continue")
            {
                SDL_SetRenderDrawColor(context.renderer, 255,255,255,255);
                SDL_RenderDrawLine(
                    context.renderer, 
                    rects["continue"].x + 5, 
                    rects["continue"].y + rects["continue"].h + 5, 
                    rects["continue"].x + rects["continue"].w - 10, 
                    rects["continue"].y + rects["continue"].h + 5
                );
            }
            if (hoverState == "mainMenu")
            {
                SDL_SetRenderDrawColor(context.renderer, 255,255,255,255);
                SDL_RenderDrawLine(
                    context.renderer, 
                    rects["mainMenu"].x + 5, 
                    rects["mainMenu"].y + rects["mainMenu"].h + 5, 
                    rects["mainMenu"].x + rects["mainMenu"].w - 10, 
                    rects["mainMenu"].y + rects["mainMenu"].h + 5
                );
            }
            if (hoverState == "restart")
            {
                SDL_SetRenderDrawColor(context.renderer, 255,255,255,255);
                SDL_RenderDrawLine(
                    context.renderer, 
                    rects["restart"].x + 5, 
                    rects["restart"].y + rects["restart"].h + 5, 
                    rects["restart"].x + rects["restart"].w - 10, 
                    rects["restart"].y + rects["restart"].h + 5
                );
            }
        }
        
    }
    else
    {
        menu.draw(context.renderer);
    }
    
}

void Window::update()
{
    if (isGame)
    {
        map.update();
    }
    else
    {
        menu.update();
    }
}


void Window::createMap()
{
    map.map = tileMap();
    map.initMap();
    map.startPos[0] = 0;
    map.startPos[1] = 0;
    map.saw = false;
    map.player.collectedItem = "none";
    map.keyCounter = 0;
    map.bobi.startPos[0] = 0;
    map.bobi.startPos[1] = 1;

    map.bobi.skullHitbox.x = 0;
    map.bobi.skullHitbox.y = 0;

    map.bobi.chinHitbox.x = 0;
    map.bobi.chinHitbox.y = 0;
}


void Window::initImages()
{
    images["menuText"] = IMG_LoadTexture(context.renderer, "img/stop/menuText.png");
    images["continue"] = IMG_LoadTexture(context.renderer, "img/stop/continue.png");
    images["mainMenu"] = IMG_LoadTexture(context.renderer, "img/stop/mainMenu.png");
    images["restart"] = IMG_LoadTexture(context.renderer, "img/stop/restart.png");
}

void Window::initImageRects()
{
    rects["menu"]     = {30, 30, 114, 42};
    rects["continue"] = {30, 100, 142, 28};
    rects["mainMenu"] = {30, 200, 142, 28};
    rects["restart"]  = {30, 150, 142, 28};
}


