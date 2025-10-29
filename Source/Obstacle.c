#include <Obstacle.h>
#include <Constants.h>

#include <stdlib.h>

void Obstacles_Free(ObstacleList* obstacles)
{
    Obstacle* it = obstacles->First;
    while (it != NULL)
    {
        Obstacle* tmp = it;
        it = it->Next;
        free(tmp);
    }

    obstacles->First = NULL;
    obstacles->Last = NULL;
}

void Obstacles_Update(ObstacleList* obstacles, float deltaTime)
{
    Obstacle* it = obstacles->First;
    while (it != NULL)
    {
        it->PositionX += OBSTACLE_SPEED_X * deltaTime;

        if (it->PositionX <= -OBSTACLE_WIDTH)
        {
            obstacles->First = it->Next;
            free(it);
            it = obstacles->First;
        }
        else
        {
            it = it->Next;
        }
    }

    if (obstacles->First == NULL)
    {
        obstacles->Last = NULL;
    }

    Obstacle* last = obstacles->Last;
    if (last == NULL || WINDOW_WIDTH - (int)last->PositionX >= OBSTACLE_SPACE_X)
    {
        Obstacle* obstacle = malloc(sizeof(Obstacle));
        obstacle->Next = NULL;
        obstacle->PositionX = WINDOW_WIDTH;

        obstacle->GapY = OBSTACLE_MIN_GAP_Y + (rand() / (float)RAND_MAX) * (OBSTACLE_MAX_GAP_Y - OBSTACLE_MIN_GAP_Y);

        if (last == NULL)
        {
            obstacles->First = obstacle;
        }
        else
        {
            if (obstacle->GapY < last->GapY + BEE_JUMP_SPEED)
            {
                obstacle->GapY = last->GapY + BEE_JUMP_SPEED;
            }

            obstacles->Last->Next = obstacle;
        }

        obstacles->Last = obstacle;
    }
}

void Obstacles_Draw(ObstacleList* obstacles, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 200, 0, 0, 255);

    Obstacle* it = obstacles->First;
    while (it != NULL)
    {
        const SDL_FRect topRect = {it->PositionX, 0, OBSTACLE_WIDTH, it->GapY};
        const SDL_FRect bottomRect = {it->PositionX, it->GapY + OBSTACLE_GAP_HEIGHT, OBSTACLE_WIDTH, WINDOW_HEIGHT - it->GapY};
        SDL_RenderFillRect(renderer, &topRect);
        SDL_RenderFillRect(renderer, &bottomRect);
        it = it->Next;
    }
}
