#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include "image.h"
struct player
{
    //SDL_Texture* j;
    int posX;
    int posY;
    // int velocity;
    // int jumpForce;
    // int state;
}; typedef struct player player_t;

void printPlayer(player_t *p, SDL_Renderer* renderer);
player_t* initPlayer(player_t *p, int x, int y);

#endif