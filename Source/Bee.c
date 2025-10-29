#include <Bee.h>
#include <Constants.h>

void Bee_Initialize(Bee* bee)
{
    bee->PositionX = BEE_START_POSITION_X;
    bee->PositionY = BEE_START_POSITION_Y;
    bee->VelocityY = 0.0f;
}

void Bee_Update(Bee* bee, float deltaTime)
{
    bee->VelocityY += BEE_GRAVITY * deltaTime;
    bee->PositionY += bee->VelocityY * deltaTime;
}

void Bee_Jump(Bee* bee)
{
    bee->VelocityY = BEE_JUMP_SPEED;
}

void Bee_Draw(Bee* bee, SDL_Renderer* renderer)
{
    const SDL_FRect rect = {bee->PositionX, bee->PositionY, BEE_SIZE, BEE_SIZE};
    SDL_SetRenderDrawColor(renderer, 160, 160, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}
