#ifndef __FLABEE_OBSTACLE__
#define __FLABEE_OBSTACLE__

#include <SDL3/SDL_render.h>

typedef struct Obstacle
{
    struct Obstacle* Next;
    float PositionX;
    float GapY;
} Obstacle;

typedef struct ObstacleList
{
    Obstacle* First;
    Obstacle* Last;
} ObstacleList;

void Obstacles_Free(ObstacleList* obstacles);
int Obstacles_Update(ObstacleList* obstacles, float deltaTime);
void Obstacles_Draw(const ObstacleList* obstacles, SDL_Renderer* renderer);

#endif
