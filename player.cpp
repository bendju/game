#include "headers/player.hpp"

Player::Player()
{
    playerSize    = 64;
    imageCounter  = 0;
    imageDelay    = 0;
    imageKey      = "right";
    collectedItem = "none";

}

void Player::draw(SDL_Renderer* renderer)
{
    if (collectedItem == "none")
    {
        SDL_RenderCopy(renderer, images[imageKey][imageCounter], NULL, &playerImage);
    }
    else if (collectedItem == "hook")
    {
        SDL_RenderCopy(renderer, images["hook_" + imageKey][imageCounter], NULL, &playerImage);
    }
    else if (collectedItem == "key")
    {
        SDL_RenderCopy(renderer, images["key_" + imageKey][imageCounter], NULL, &playerImage);
    }
    else if (collectedItem == "saw")
    {
        SDL_RenderCopy(renderer, images["saw_" + imageKey][imageCounter], NULL, &playerImage);
    }

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    // SDL_RenderDrawRect(renderer, &hitbox);
}

void Player::update()
{
    setDirection();
    imageDelay++;
    if (imageDelay % 15 == 0)
    {
        if (imageCounter < 3)
        {
            imageCounter += 1;
        }
        else 
        {
            imageCounter = 0;
        }
    }
    
}

void Player::init(int width, int height, SDL_Renderer* renderer)
{
    screenWidth = width;
    screenHeight = height;

    playerImage.x = screenWidth / 2 - playerSize / 2;
    playerImage.y = screenHeight / 2 - playerSize / 2;
    playerImage.w = playerSize;
    playerImage.h = playerSize;

    hitbox.x = playerImage.x + 20;
    hitbox.y = playerImage.y + 16;
    hitbox.w = 24;
    hitbox.h = 48;

    initImages(renderer);

}

void Player::initImages(SDL_Renderer* renderer)
{
    loadImage("idle", renderer);
    loadImage("top", renderer);
    loadImage("down", renderer);
    loadImage("left", renderer);
    loadImage("right", renderer);

    loadImage("hook_idle", renderer);
    loadImage("hook_top", renderer);
    loadImage("hook_down", renderer);
    loadImage("hook_left", renderer);
    loadImage("hook_right", renderer);

    loadImage("key_idle", renderer);
    loadImage("key_top", renderer);
    loadImage("key_down", renderer);
    loadImage("key_left", renderer);
    loadImage("key_right", renderer);

    loadImage("saw_idle", renderer);
    loadImage("saw_top", renderer);
    loadImage("saw_down", renderer);
    loadImage("saw_left", renderer);
    loadImage("saw_right", renderer);
}

void Player::loadImage(std::string type, SDL_Renderer* renderer)
{
    std::vector<SDL_Texture*> newImages;
    for (int i = 0; i < 4; i++)
    {
        std::string path = "img/player/" + type + "/w" + std::to_string(i) + ".png";
        SDL_Texture* image = IMG_LoadTexture(renderer, path.c_str());
        newImages.push_back(image);
    }
    images[type] = newImages;
}


void Player::setDirection()
{
    const Uint8* state = SDL_GetKeyboardState(NULL);
    bool isIdle        = false;

    if (state[SDL_SCANCODE_W])
    {
        imageKey = "top";
        isIdle = true;
    }
    if (state[SDL_SCANCODE_S])
    {
        imageKey = "down";
        isIdle = true;
    }
    if (state[SDL_SCANCODE_A])
    {
        imageKey = "left";
        isIdle = true;
    }
    if (state[SDL_SCANCODE_D])
    {
        imageKey = "right";
        isIdle = true;
    }

    if (!isIdle)
    {
        imageKey = "idle";
    }
}