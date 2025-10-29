#include <Collision.h>
#include <Constants.h>

bool IsCollide(Bee* bee, ObstacleList* obstacles)
{
    float beeTop = bee->PositionY;
    float beeBottom = bee->PositionY + BEE_SIZE;

    if (beeTop < 0.0f || beeBottom > WINDOW_HEIGHT)
    {
        return true;
    }

    float beeLeft = BEE_POSITION_X;
    float beeRight = BEE_POSITION_X + BEE_SIZE;

    Obstacle* it = obstacles->First;
    while (it != NULL)
    {
        if (beeLeft < it->PositionX + OBSTACLE_WIDTH && beeRight > it->PositionX)
        {
            if (beeTop <= it->GapY || beeBottom >= it->GapY + OBSTACLE_GAP_HEIGHT)
            {
                return true;
            }
        }

        it = it->Next;
    }

    return false;
}
