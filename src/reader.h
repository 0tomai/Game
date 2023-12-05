#ifndef READER_H
#define READER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "image.h"

void tailleFichier(int* nbLigne, int* nbCol, int* nbChar, char path[]);

int** init_tab(int l, int c);

void fill_tab(int** tab, char path[]);

void reading(char map[], SDL_Rect* r);

#endif