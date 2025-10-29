#ifndef __FLABEE_OBSTACLE__
#define __FLABEE_OBSTACLE__

#include <Constants.h>
#include <SDL3/SDL_render.h>

#define OBSTACLE_WIDTH (WINDOW_WIDTH / 12.0f)
#define OBSTACLE_SPACE_X (WINDOW_WIDTH / 4)
#define OBSTACLE_SPEED_X (WINDOW_WIDTH / -6.0f)
#define OBSTACLE_GAP_SIZE (WINDOW_HEIGHT / 4.0f)
#define OBSTACLE_MIN_GAP_Y (OBSTACLE_GAP_SIZE / 2.0f)
#define OBSTACLE_MAX_GAP_Y (WINDOW_HEIGHT - OBSTACLE_MIN_GAP_Y - OBSTACLE_GAP_SIZE)

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
void Obstacles_Update(ObstacleList* obstacles, float deltaTime);
void Obstacles_Draw(ObstacleList* obstacles, SDL_Renderer* renderer);

#endif
