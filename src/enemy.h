#ifndef ENEMY_H
#define ENEMY_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



typedef struct enemy
{
    int posX;
    int posY;
    int velocity;
    int dirX;
    int hp;
    struct enemy* next; 
} enemy_t;

void readEnemy(enemy_t* e[], char path[]);

void readEnemyList(enemy_t* e, char path[]);
void prepare_enemies_list(SDL_Rect* enemy, enemy_t* e, int nbEnemies);

void print_enemies(SDL_Rect* enemy, int nbEnemies, SDL_Renderer* render, SDL_Texture* texture);

void prepare_enemies(SDL_Rect* enemy, enemy_t* e[], int nbEnemies);

void linkedCreate(enemy_t* e, int hp, int posX, int posY);
void removeEnemy(enemy_t* head, enemy_t* target, SDL_Rect *enemies, int *nbEnemies, int index);

void gravityE(SDL_Rect enemy);

#endif