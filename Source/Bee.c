#include <Bee.h>
#include <Constants.h>
#include <Assets.h>

void Bee_Initialize(Bee* bee)
{
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
    float frame = 0;
    if (bee->VelocityY < BEE_JUMP_SPEED / 2)
    {
        frame = 1;
    }
    else if (bee->VelocityY < 0)
    {
        frame = 2;
    }

    const SDL_FRect srcRect = {frame * BEE_SPRITE_SIZE, 0, BEE_SPRITE_SIZE, BEE_SPRITE_SIZE};
    const SDL_FRect dstRect = {BEE_POSITION_X, bee->PositionY, BEE_SIZE, BEE_SIZE};
    SDL_RenderTexture(renderer, Assets.Bee, &srcRect, &dstRect);
}
