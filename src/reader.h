#ifndef READER_H
#define READER_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

void tailleFichier();

int** remplirTableau(int l, int c);

void read(SDL_Renderer* renderer);

#endif