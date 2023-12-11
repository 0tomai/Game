#ifndef COLLISION_H
#define COLLISION_H


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL_ttf.h>
#include "image.h"
#include "player.h"
#include "enemy.h"

typedef enum {
    NO_COLLISION,
    TOP_COLLISION,
    BOTTOM_COLLISION,
    LEFT_COLLISION,
    RIGHT_COLLISION,
    SAD_COLLISION
} CollisionType;

CollisionType collisions(player_t *p, SDL_Rect rects[], int numRects);
CollisionType collisionsEnemy(SDL_Rect e, SDL_Rect rects[], int numRects);
bool playerEnemyCollision(player_t *player, SDL_Rect enemy);
#endif // COLLISION_H
