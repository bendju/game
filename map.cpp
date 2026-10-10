#include "headers/map.hpp"
#include "headers/tileMap.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <filesystem>
#include <cmath>

std::random_device  rd;
std::mt19937 gen(rd());

Map::Map()
{
    vibrateLeft   = false;
    gameOver      = false;
    keyCounter    = 0;
    collectedItem = "null";
    playerSize    = 64;
    gridSize      = 64;
    startPos[0]   = 0;
    startPos[1]   = 0;
    saw           = false;
    speed         = 5;
    map           = tileMap();
}

void Map::draw(SDL_Renderer* renderer)
{
    if (gameOver)
    {
        SDL_SetRenderDrawColor(renderer, 3,3,3,255);
        SDL_Rect bgRect = {0,0, screenWidth, screenHeight};
        SDL_RenderFillRect(renderer, &bgRect);

        SDL_Rect skullRect = {screenWidth / 2 - 100, screenHeight / 3 - 100, 200,200};
        SDL_RenderCopy(renderer, tiles["skull"], NULL, &skullRect);

        SDL_RenderCopy(renderer, gameOverImg, NULL, &gameOverRect);
        SDL_RenderCopy(renderer, continueImg, NULL, &continueRect);
        return;
    }
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
            if (map[i][j] == 0)
            {
                continue;
            }
            else
            {
                SDL_Rect rect = {j * gridSize + startPos[1], i * gridSize + startPos[0], gridSize, gridSize};
                SDL_RenderCopy(renderer, tiles[std::to_string(map[i][j])], NULL, &rect);
            }
        }
    }
    bobi.draw(renderer);

    SDL_Rect rect = {0,0, screenWidth, screenHeight};
    double distance = std::sqrt(std::pow(bobi.skullHitbox.x - screenWidth / 2, 2) + std::pow(bobi.skullHitbox.y - screenHeight / 2, 2));
    if (distance < 300 && false)
    {
        SDL_RenderCopy(renderer, narrow_light, NULL, &rect);
        bobi.imageDelay++;
        if (bobi.imageDelay == 15)
        {
            bobi.chinPadding += 15;
        }
        if (bobi.imageDelay >= 30)
        {
            bobi.chinPadding -= 15;
            bobi.imageDelay = 0;
        }
    }
    else
    {
        SDL_RenderCopy(renderer, light, NULL, &rect);
        bobi.imageDelay  = 0;
        bobi.chinPadding = 0;
    }
    
    
    player.draw(renderer);

}

Vec2 Map::direction()
{
    Vec2 newDirection = {0,0};
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_W])
    {
        newDirection.x = 1;
    }
    if (state[SDL_SCANCODE_S])
    {
        newDirection.x = -1;
    }
    if (state[SDL_SCANCODE_A])
    {
        newDirection.y = 1;
    }
    if (state[SDL_SCANCODE_D])
    {
        newDirection.y = -1;
    }
    return newDirection;

}

void Map::move(Vec2 dir)
{
    if (dir.x != 0 && dir.y != 0)
    {
        startPos[0] += dir.x * speed / 1.41421;
        startPos[1] += dir.y * speed / 1.41421;
    }
    else
    {
        startPos[0] += dir.x * speed;
        startPos[1] += dir.y * speed;
    }
}

void Map::update()
{
    if (gameOver)
    {
        return;
    }

    bobi.update(startPos[0], startPos[1]);
    player.update();
    checkMoving();
    pickUpItem();
    vibration();

    if ((SDL_HasIntersection(&player.hitbox, &bobi.skullHitbox) || SDL_HasIntersection(&player.hitbox, &bobi.chinHitbox)) && !gameOver)
    {
        gameOver = true;
    }

}

void Map::pickUpItem()
{
    const Uint8* state = SDL_GetKeyboardState(NULL);
    
    if (!state[SDL_SCANCODE_SPACE])
        return;

    int playerX = screenWidth / 2 - 32;
    int playerY = screenHeight / 2 - 32;

    SDL_Rect playerRect = { playerX, playerY, 64, 64 };

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] != 7 && map[i][j] != 8 && map[i][j] != 9 && map[i][j] != 122 && map[i][j] != 3 && map[i][j] != 170 && map[i][j] != 171)
                continue;

            SDL_Rect tileRect =
            {
                j * gridSize + startPos[1],
                i * gridSize + startPos[0],
                gridSize,
                gridSize
            };

            if (SDL_HasIntersection(&playerRect, &tileRect))
            {
                if (map[i][j] == 7 || map[i][j] == 8 || map[i][j] == 9)
                {
                    if (collectedItem == "hook")
                    {
                        collectedItem = "key";
                        player.collectedItem = "key";
                        map[i][j] = 4;
                        return; 
                    }
                }
                if (map[i][j] == 122 && collectedItem != "hook")
                {
                    collectedItem = "hook";
                    player.collectedItem = "hook";
                    map[i][j] = 123;
                    return;
                }
                if (map[i][j] == 3)
                {
                    if (collectedItem == "key")
                    {
                        keyCounter++;
                        collectedItem = "null";
                        player.collectedItem = "none";

                        if (keyCounter == 3)
                        {
                            player.collectedItem = "saw";
                            map[i][j] = 2;
                            saw = true;
                        }
                        return;
                    }
                }
                if (map[i][j] == 170 || map[i][j] == 171)
                {
                    if (saw)
                    {
                        finish();
                        saw = false;
                        break;
                    }
                }
            }
        }
    }
}

void Map::checkMoving()
{
    int playerX = screenWidth / 2 - gridSize / 2 + 20;
    int playerY = screenHeight / 2 - gridSize / 2 + 16;
    int padding = (gridSize - playerSize) / 2;

    Vec2 dir = direction();

    // ===== X MOZGÁS =====

    bool canMoveX = true;

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] <= 100 )
                continue;
            if (map[i][j] == 121 || map[i][j] == 170 || map[i][j] == 171 || map[i][j] == 122 || map[i][j] == 123)
                continue;

            int rectX = j * gridSize + startPos[1] + dir.y * speed - padding;
            int rectY = i * gridSize + startPos[0] - padding;

            if (
                playerX < rectX + gridSize &&
                playerX + 24 > rectX &&
                playerY < rectY + gridSize &&
                playerY + 48 > rectY
            )
            {
                canMoveX = false;
            }
        }
    }

    if (canMoveX)
    {
        startPos[1] += dir.y * speed;
        bobi.chinHitbox.x += dir.y * speed;
        bobi.skullHitbox.x += dir.y * speed;
    }

    // ===== Y MOZGÁS =====

    bool canMoveY = true;

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] <= 100)
                continue;
            if (map[i][j] == 121 || map[i][j] == 170 || map[i][j] == 171 || map[i][j] == 122 || map[i][j] == 123)
                continue;

            int rectX = j * gridSize + startPos[1] - padding;
            int rectY = i * gridSize + startPos[0] + dir.x * speed - padding;

            if (
                playerX < rectX + gridSize &&
                playerX + 24 > rectX &&
                playerY < rectY + gridSize &&
                playerY + 48 > rectY
            )
            {
                canMoveY = false;
            }
        }
    }

    if (canMoveY)
    {
        startPos[0] += dir.x * speed;
        bobi.chinHitbox.y += dir.x * speed;
        bobi.skullHitbox.y += dir.x * speed;
    }
}

void Map::init(int width, int height, SDL_Renderer* renderer, bool* isGame)
{
    bobi.init(width, height, renderer);
    gameOverImg  = IMG_LoadTexture(renderer, "img/gameover/gameover.png");
    gameOverRect = {width / 2 - 152, height /2, 304, 56};

    continueImg  = IMG_LoadTexture(renderer, "img/gameover/restart.png");
    continueRect = {width / 2 - 100, height - height / 4, 200, 14};

    screenWidth  = width;
    screenHeight = height;
    initTiles(renderer);

    light = IMG_LoadTexture(renderer, "narrow_light.png");
    narrow_light = IMG_LoadTexture(renderer, "img/narrow_light.png");
    tiles["skull"] = IMG_LoadTexture(renderer, "img/bobi/skull2.png");
    initMap();
    isGameP = isGame;
    player.init(width, height, renderer);
}

void Map::initTiles(SDL_Renderer* renderer)
{
    for (const auto& entry : std::filesystem::directory_iterator("img/"))
    {
        if (entry.is_regular_file())
        {
            std::string extension = entry.path().extension().string();
            std::string filename = entry.path().filename().string();
            if (extension == ".png")
            {
                std::string fullpath = "img/" + filename;
                std::string key = filename.substr(0, filename.find_last_of('.'));
                SDL_Texture* tile = IMG_LoadTexture(renderer, fullpath.c_str());
                tiles[key] = tile;
            }
        }
    }
}

void Map::initMap()
{
    std::vector<std::vector<int>> walls;
    std::vector<std::vector<int>> floors;

    int floor = 5;
    int wall = 121;

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j] == wall)
                walls.push_back({i, j});

            if (map[i][j] == floor)
                floors.push_back({i, j});
        }
    }

    std::shuffle(floors.begin(), floors.end(), gen);
    std::shuffle(walls.begin(), walls.end(), gen);

    for (int i = 0; i < 3 && i < floors.size(); i++)
    {
        int row = floors[i][0];
        int col = floors[i][1];
        map[row][col] = 7 + i;
    }

    if (floors.size() > 3)
    {
        map[floors[3][0]][floors[3][1]] = 3;
    }

    for (int i = 0; i < 3 && i < walls.size(); i++)
    {
        int row = walls[i][0];
        int col = walls[i][1];
        map[row][col] = 122;
    }
}


void Map::finish()
{
    (*isGameP) = false;
    std::cout << "vege";
}


void Map::vibration()
{
    double distance = std::sqrt(std::pow(bobi.skullHitbox.x - screenWidth / 2, 2) + std::pow(bobi.skullHitbox.y - screenHeight / 2, 2));
    if (distance < 250)
    {
        bobi.imageKey = "blod_skull";
        if (vibrateLeft)
        {
            startPos[1] += 15;
            vibrateLeft = !vibrateLeft;
            return;
        }
        else
        {
            startPos[1] -= 15;
            vibrateLeft = !vibrateLeft;
        }
    }
    else
    {
        bobi.imageKey = "skull";
    }
}
