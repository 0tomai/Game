#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



struct enemy
{
    int posX;
    int posY;
    int velocity;
    int dirX;
    int hp;
}; typedef struct enemy enemy_t;

void readEnemy(enemy_t* e[], char path[]);

#endif