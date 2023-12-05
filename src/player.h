#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include "image.h"
///#include "collision.h"

struct player
{
    float posX;
    int posY;
    int velocity;
    int velocityY;
    int dirX;
    int canJump;
    int is_jumping;
    int timer;
    int nbJumpCan;
    int nbJump;
}; typedef struct player player_t;

void printPlayer(player_t *p, SDL_Renderer* renderer, SDL_Rect* destRect, SDL_Texture* texture);
player_t* initPlayer(player_t *p, float x, int y);
void move(player_t *p, int dir);
void updatePlayerPosition(player_t *p, float deltaTime);
void gravity(SDL_Rect rects[], int numRects, float deltaTime, player_t*p);
void jump(SDL_Rect rects[], int numRects, float deltaTime);
#endif
