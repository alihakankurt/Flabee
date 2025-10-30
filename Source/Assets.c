#include <Assets.h>

#include <SDL3_image/SDL_image.h>

struct Assets Assets = {0};

bool Assets_Load(SDL_Renderer* renderer)
{
    Assets.Background = IMG_LoadTexture(renderer, "./Assets/Images/Background.png");
    if (!Assets.Background)
    {
        return false;
    }

    Assets.Bee = IMG_LoadTexture(renderer, "./Assets/Images/Bee.png");
    if (!Assets.Bee)
    {
        SDL_DestroyTexture(Assets.Background);
        return false;
    }

    Assets.Obstacle = IMG_LoadTexture(renderer, "./Assets/Images/Obstacle.png");
    if (!Assets.Obstacle)
    {
        SDL_DestroyTexture(Assets.Background);
        SDL_DestroyTexture(Assets.Bee);
        return false;
    }

    Assets.Scoreboard = IMG_LoadTexture(renderer, "./Assets/Images/Scoreboard.png");
    if (!Assets.Scoreboard)
    {
        SDL_DestroyTexture(Assets.Background);
        SDL_DestroyTexture(Assets.Bee);
        SDL_DestroyTexture(Assets.Obstacle);
        return false;
    }

    Assets.Digits = IMG_LoadTexture(renderer, "./Assets/Images/Digits.png");
    if (!Assets.Digits)
    {
        SDL_DestroyTexture(Assets.Background);
        SDL_DestroyTexture(Assets.Bee);
        SDL_DestroyTexture(Assets.Obstacle);
        SDL_DestroyTexture(Assets.Scoreboard);
        return false;
    }

    SDL_SetTextureScaleMode(Assets.Background, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureScaleMode(Assets.Bee, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureScaleMode(Assets.Obstacle, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureScaleMode(Assets.Scoreboard, SDL_SCALEMODE_NEAREST);
    SDL_SetTextureScaleMode(Assets.Digits, SDL_SCALEMODE_NEAREST);
    return true;
}

void Assets_Unload()
{
    SDL_DestroyTexture(Assets.Background);
    SDL_DestroyTexture(Assets.Bee);
    SDL_DestroyTexture(Assets.Obstacle);
    SDL_DestroyTexture(Assets.Scoreboard);
    SDL_DestroyTexture(Assets.Digits);
}
