#ifndef __FLABEE_GAME__
#define __FLABEE_GAME__

#include <Assets.h>
#include <Bee.h>
#include <Obstacle.h>
#include <SDL3/SDL.h>

typedef enum GameState
{
    GAME_QUIT,
    GAME_PLAYING,
    GAME_DEATH,
} GameState;

typedef struct Game
{
    SDL_Window* Window;
    SDL_Renderer* Renderer;
    Bee Beee;
    ObstacleList Obstacles;
    int Score;
    int BestScore;
    GameState State;
} Game;

int Game_Run();

#endif
