#include "enemy.h"

//Fonction non utilisée, permettait de lire et créer les différents ennemis avec un tableau
void readEnemy(enemy_t* e[], char path[]){
    FILE* f;
    char c;
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
                checkPosX++;
            }
            if (checkHP == 0)
            {
                checkHP++;
                e[numEnemy]->hp = truc;
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
    fclose(f);

}

void linkedCreate(enemy_t* e, int hp, int posX, int posY){
    enemy_t* current = e;
    if (current->hp == -1)
    {
        current->hp = hp;
        current->posX = posX;
        current->posY = posY; 
    }
    else
    {
        while (current->next != NULL)
    {
        current = current->next;
    }

    current->next = malloc(sizeof(enemy_t));
    current->next->hp = hp;
    current->next->posX = posX;
    current->next->posY = posY; 
    current->next->next = NULL;
    }
    
    
}

//Procedure qui permet la lecture et l'ajout d'ennemies dans une liste chainée passée en paramètre
void readEnemyList(enemy_t* e, char path[]){
    FILE* f;
    char c;
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
            for (int j = 0; j < 10; j++) //reset le tableau de charactère pour en ajouter de nouveaux
            {
                param[j] = '\0';
            }
            
            if (checkHP != 0 && checkPosX != 0)
            {
                checkPosY = truc;
            }
            if (checkHP != 0 && checkPosX == 0)
            {
                checkPosX = truc;
                
            }
            if (checkHP == 0)
            {
                checkHP = truc;
            }
            if(checkPosY != 0){
                linkedCreate(e, checkHP, checkPosX, checkPosY);
                checkPosY = 0;
                checkHP = 0;
                checkPosX = 0;
            }
                        
            i = 0;
        }
        if (isNumber == 1)
        {
            if (c >= 48 && c<= 57) //test le caractère donné dans le fichier texte pour verifier s'il s'agit bien d'un chiffre
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
    fclose(f);
}

//procedure qui initialise les SDL_Rect correspondant aux ennemis
void prepare_enemies_list(SDL_Rect* enemy, enemy_t* e, int nbEnemies){
    enemy_t* current = e;
    for (int i = 0; i < nbEnemies; i++)
    {
        enemy[i].h = 36;
        enemy[i].w = 36;
        enemy[i].x = current->posX;
        enemy[i].y = current->posY;
        current = current->next;
    }
}

//procedure qui initialise les SDL_Rect correspondant aux ennemis, inutilisée car la liste chainée est utilisée
void prepare_enemies(SDL_Rect* enemy, enemy_t* e[], int nbEnemies){
    for (int i = 0; i < nbEnemies; i++)
    {
        enemy[i].h = 36;
        enemy[i].w = 36;
        enemy[i].x = e[i]->posX;
        enemy[i].y = e[i]->posY;
    }
}

//procedure qui permet l'affichage des ennemis 
void print_enemies(SDL_Rect* enemy, int nbEnemies, SDL_Renderer* render, SDL_Texture* texture){
    for (int i = 0; i < nbEnemies; i++)
    {
        SDL_RenderCopy(render, texture, NULL, &enemy[i]);
    }
}

//procedure pour l'ecriture fichier du nombre d'ennemis tués pdt une partie
void write_killed_enemies(char path[], int killed){
    FILE* f;
    f = fopen(path, "a+");
    fprintf(f, "%d", killed);
    fprintf(f, ",\n");
    fclose(f);
}

//procedure de retrait d'un ennemi dans la liste chainée
void removeEnemy(enemy_t** head, enemy_t* target, SDL_Rect *enemies, int *nbEnemies, int index) {
    enemy_t* current = *head;
    enemy_t* previous = NULL;
    if(*head == target)
    {
        printf("OK\n");
        printf("HPNEXT: %d\n", (*head)->next->hp);
        *head = current->next;
        printf("HPNOOW: %d\n", (*head)->hp);
        for (int i = index; i < *nbEnemies - 1; ++i) {
        enemies[i] = enemies[i + 1];
    }
    (*nbEnemies)--;
    printf("nbEnemies %d\n", *nbEnemies);
        return;
    }
    while (current != NULL) {
        if (current == target) {
            if (previous == NULL) {
                printf("YES\n");
                if (current->next != NULL) {
                    //*head = current->next;
                } else {
                    break;
                }
            } else {
                previous->next = current->next;
            }
            free(current);
            break;
        }
        previous = current;
        current = current->next;
    }

    

    for (int i = index; i < *nbEnemies - 1; ++i) {
        enemies[i] = enemies[i + 1];
    }
    (*nbEnemies)--;
    printf("nbEnemies %d\n", *nbEnemies);
}

// void removeEnemy(enemy_t** head, enemy_t* target, SDL_Rect *enemies, int *nbEnemies, int index) {
//     enemy_t* current = *head;
//     enemy_t* previous = NULL;
//     while (current != NULL) {

//         if (current == target) {
//             if (previous == NULL) {
//                 if(current->next != NULL)
//                 {
//                     *head = current->next;
//                 }else 
//                 {
//                     break;
//                 }
//             } else {
//                 previous->next = current->next;
//             }
//             printf("SUPPRESION\n");
//             free(current);
//             break;
//         }

//         previous = current;
//         current = current->next;

//     }


//     printf("index %d\n", index);
//     printf("nbEnemies %d\n", *nbEnemies);
    
// for (int i = index; i < *nbEnemies - 1; ++i) {
//     enemies[i] = enemies[i + 1];
// }
// (*nbEnemies)--;
// }

