#include "headers/bobi.hpp"
#include <cmath>
#include <iostream>


Bobi::Bobi()
{
    chinPadding = 0;
    imageDelay  = 0;
    startPos[0] = 0;
    startPos[1] = 1;
    skullHitbox = {0, 0, 108, 117};
    chestHitbox = {0, 0, 50, 50};
    chinHitbox  = {0, 0, 64, 28};
    speed       = 5;
    imageKey    = "skull";
}


void Bobi::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255,0,0,255);
    // SDL_RenderDrawRect(renderer, &skullHitbox);
    // SDL_RenderDrawRect(renderer, &chestHitbox);

    SDL_RenderCopy(renderer, images[imageKey], NULL, &skullHitbox);
    SDL_RenderCopy(renderer, images["chin"], NULL, &chinHitbox);
}

void Bobi::init(int width, int height, SDL_Renderer* renderer)
{
    screenWidth  = width;
    screenHeight = height;

    images["skull"] = IMG_LoadTexture(renderer, "img/bobi/skull2.png");
    images["blod_skull"] = IMG_LoadTexture(renderer, "img/bobi/skull3.png");
    images["chest"] = IMG_LoadTexture(renderer, "img/bobi/chest.png");
    images["bone"]  = IMG_LoadTexture(renderer, "img/bobi/bone.png");
    images["chin"]  = IMG_LoadTexture(renderer, "img/bobi/all.png");

}

void Bobi::update(int paddX, int paddY)
{
    int centerX = screenWidth / 2;
    int centerY = screenHeight / 2;

    int vec[2]     = {centerX - skullHitbox.x, centerY - skullHitbox.y};
    double vecSize = std::sqrt(std::pow(vec[0], 2) + std::pow(vec[1], 2));
    dealer         = vecSize / speed;


    if (vecSize > 1000)
    {
        skullHitbox.x += vec[0] - 300;
        skullHitbox.y += vec[1] - 300;

        chinHitbox.x += vec[0] - 300;
        chinHitbox.y += vec[1] - 300;

    }

    if (vecSize > 600)
    {
        dealer = 1;
    }

    if (dealer > 2)
    {
        skullHitbox.x += vec[0] / dealer;
        skullHitbox.y += vec[1] / dealer;

        chinHitbox.x = skullHitbox.x + 22;
        chinHitbox.y = skullHitbox.y + 120 + chinPadding;
    }
}
