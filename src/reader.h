#ifndef READER_H
#define READER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

void tailleFichier(int* nbLigne, int* nbCol);

int** init_tab(int l, int c);

void fill_tab(int** tab);

void read(SDL_Renderer* renderer);

#endif