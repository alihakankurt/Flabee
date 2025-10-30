#ifndef __FLABEE_COLLISION__
#define __FLABEE_COLLISION__

#include <stdbool.h>
#include <Bee.h>
#include <Obstacle.h>

bool IsCollide(const Bee* bee, const ObstacleList* obstacles);

#endif
