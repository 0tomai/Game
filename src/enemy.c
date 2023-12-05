#include "enemy.h"

void readEnemy(enemy_t* e[], char path[]){
    FILE* f;
    char c;
    char strc[1];
    char param[10];
    int isNumber = 0;
    int checkHP = 0;
    int checkPosX = 0;
    int checkPosY = 0;
    int i = 0;
    int numEnemy = 0;
    int truc=0;
    f = fopen(path, "r");
    c = fgetc(f);
    while (c != EOF)
    {
        if (c == ':')
        {
            isNumber = 1;
            c = fgetc(f);
        }
        if (c== '/')
        {
            
            
            isNumber = 0;
            truc = atoi(param);
            for (int j = 0; j < 10; j++)
            {
                param[j] = '\0';
            }
            
            
            if (checkHP == 1 && checkPosX == 1)
            {
                checkPosY = 1;
                e[numEnemy]->posY = truc;
            }
            if (checkHP == 1 && checkPosX == 0)
            {
                e[numEnemy]->posX = truc;
                //e[1]->posX = truc;
                checkPosX++;
            }
            if (checkHP == 0)
            {
                checkHP++;
                e[numEnemy]->hp = truc;
                //e[1]->hp = truc;
            }
            if(checkPosY == 1){
                checkPosY = 0;
                checkHP = 0;
                checkPosX = 0;
                numEnemy++;
            }
                        
            i = 0;
        }
        if (isNumber == 1)
        {
            strc[0] = c;
            if (c >= 48 && c<= 57)
            {
                param[i] = c;
                i++;
            }
            else
            {
                printf("Tout caractère non numerique sera IGNORE\n");
            }
            
            
            
        }

        c = fgetc(f);        
    }
  
}

void prepare_enemies(SDL_Rect* enemy, enemy_t* e[], int nbEnemies){
    for (int i = 0; i < nbEnemies; i++)
    {
        enemy[i].h = 36;
        enemy[i].w = 36;
        enemy[i].x = e[i]->posX;
        enemy[i].y = e[i]->dirX;
    }
}

void print_enemies(SDL_Rect* enemy, int nbEnemies, SDL_Renderer* render, SDL_Texture* texture){
    for (int i = 0; i < nbEnemies; i++)
    {
        SDL_RenderCopy(render, texture, NULL, &enemy[i]);
        printf("%d \n", enemy[i].x);
    }
}

