#ifndef CHECKPOINT_H
#define CHECKPOINT_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

struct chp
{
    int posX;
    int posY;
}; typedef struct chp chp_t;

void printChp(SDL_Rect* r, SDL_Renderer* render, SDL_Texture* texture);

#endif