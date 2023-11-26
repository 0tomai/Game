#ifndef COLLISION_H
#define COLLISION_H


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include "image.h"
#include "player.h"

typedef enum {
    NO_COLLISION,
    TOP_COLLISION,
    BOTTOM_COLLISION,
    LEFT_COLLISION,
    RIGHT_COLLISION
} CollisionType;

CollisionType collisions(player_t *p, SDL_Rect rects[], int numRects);
#endif // COLLISION_H
