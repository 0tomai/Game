#include "collision.h"

CollisionType collisions(player_t *p, SDL_Rect rects[], int numRects)
{
    for (int i = 0; i < numRects; i++)
    {
        if (p->posX + 32 > rects[i].x && p->posX < rects[i].x + rects[i].w && p->posY + 32 > rects[i].y && p->posY < rects[i].y + rects[i].h)
        {
            int bottomDistance = rects[i].y + rects[i].h - p->posY;
            int topDistance = p->posY + 32 - rects[i].y;
            int rightDistance = rects[i].x + rects[i].w - p->posX;
            int leftDistance = p->posX + 32 - rects[i].x;

            if (bottomDistance <= topDistance && bottomDistance <= leftDistance && bottomDistance <= rightDistance)
            {
                SDL_Rect blockAbove = {rects[i].x, rects[i].y + rects[i].h, rects[i].w, rects[i].h};
                for(int j = 0; j < numRects; j++)
                {
                    if(rects[j].x == blockAbove.x && rects[j].y == blockAbove.y)
                    {
                        return SAD_COLLISION;
                    }
                }
                return BOTTOM_COLLISION;
            }
            else if (topDistance <= bottomDistance && topDistance <= leftDistance && topDistance <= rightDistance)
            {
                return TOP_COLLISION;
            }
            else if (rightDistance <= leftDistance && rightDistance <= bottomDistance && rightDistance <= topDistance)
            {
                return RIGHT_COLLISION;
            }
            else
            {
                return LEFT_COLLISION;
            }
        }
    }

    return NO_COLLISION;
}
CollisionType collisionsEnemy(SDL_Rect e, SDL_Rect rects[], int numRects)
{
    for (int i = 0; i < numRects; i++)
    {
        if (e.x + 32 > rects[i].x && e.x < rects[i].x + rects[i].w && e.y + 32 > rects[i].y && e.y < rects[i].y + rects[i].h)
        {
            int bottomDistance = rects[i].y + rects[i].h - e.y;
            int topDistance = e.y + 32 - rects[i].y;
            int rightDistance = rects[i].x + rects[i].w - e.x;
            int leftDistance = e.x + 32 - rects[i].x;

            if (bottomDistance <= topDistance && bottomDistance <= leftDistance && bottomDistance <= rightDistance)
            {
                SDL_Rect blockAbove = {rects[i].x, rects[i].y + rects[i].h, rects[i].w, rects[i].h};
                for(int j = 0; j < numRects; j++)
                {
                    if(rects[j].x == blockAbove.x && rects[j].y == blockAbove.y)
                    {
                        return SAD_COLLISION;
                    }
                }
                return BOTTOM_COLLISION;
            }
            else if (topDistance <= bottomDistance && topDistance <= leftDistance && topDistance <= rightDistance)
            {
                return TOP_COLLISION;
            }
            else if (rightDistance <= leftDistance && rightDistance <= bottomDistance && rightDistance <= topDistance)
            {
                return RIGHT_COLLISION;
            }
            else
            {
                return LEFT_COLLISION;
            }
        }
    }

    return NO_COLLISION;
}

bool playerEnemyCollision(player_t *player, SDL_Rect enemy) {
    if (player->posX + 32 > enemy.x && player->posX < enemy.x + enemy.w &&
        player->posY + 32 > enemy.y && player->posY < enemy.y + enemy.h) {
        return true;
    }
    return false;
}
