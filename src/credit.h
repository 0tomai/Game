#ifndef CREDIT_H
#define CREDIT_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>

SDL_Renderer* init_credit(SDL_Window* f);
    
void refresh_credit(SDL_Renderer* f);

void free_credit();

#endif