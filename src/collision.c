#include "collision.h"
#include <stdbool.h>

CollisionType collisions(player_t *p, SDL_Rect rects[], int numRects)
{
    for (int i = 0; i < numRects; i++)
    {
        if (p->posY + 32 > rects[i].y && p->posY < rects[i].y + rects[i].h && p->posX + 32 > rects[i].x && p->posX < rects[i].x + rects[i].w)
        {
            int bottomDistance = rects[i].y + rects[i].h - p->posY;
            int topDistance = p->posY + 32 - rects[i].y;
            int leftDistance = p->posX + 32 - rects[i].x;
            int rightDistance = rects[i].x + rects[i].w - p->posX;

            if (bottomDistance <= topDistance && bottomDistance <= leftDistance && bottomDistance <= rightDistance)
            {
                return BOTTOM_COLLISION;
            }
            else if (topDistance <= bottomDistance && topDistance <= leftDistance && topDistance <= rightDistance)
            {
                return TOP_COLLISION;
            }
            else if (leftDistance <= bottomDistance && leftDistance <= topDistance && leftDistance <= rightDistance)
            {
                return LEFT_COLLISION;
            }
            else
            {
                return RIGHT_COLLISION;
            }
        }
    }

    return NO_COLLISION;
}
