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
            param[0] = '\0';
            if (checkHP == 1 && checkPosX == 0)
            {
                e[0]->posX = truc;
                e[1]->posX = truc;
                checkPosX++;
            }
            if (checkHP == 0)
            {
                checkHP++;
                e[0]->hp = truc;
                e[1]->hp = truc;

            }
            
                        
            i = 0;
        }
        if (isNumber == 1)
        {
            strc[0] = c;
            param[i] = c;
            i++;
        }

        c = fgetc(f);        
    }
    e[0]->posY = truc;
    e[1]->posY = truc;
  
}
