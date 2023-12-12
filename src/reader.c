#include "reader.h"
#include <string.h>


void tailleFichier(int* nbLigne, int* nbCol, int* nbChar, char path[])
{
    int taille = 0;
    int max = 0;
    int colonne = 0;
    int nbUn = 0;
    char c;
    FILE* f;
    f = fopen(path, "r");
    c = fgetc(f);
    

    while(c != EOF)
    {
        if (c != '\n')
        {
            taille ++;
        }
        
        if(c == '\n')
        {
            colonne ++;
            if(max < taille)
            {
                max = taille;
            }
            taille = 0;
        }
        if(c == '1'){
        nbUn++;
        }
        c = fgetc(f);
    }
    if (c == EOF)
    {
        colonne ++;
            if(max < taille)
            {
                max = taille;
            }
    }
    
    max = max;
    colonne = colonne;
    *nbCol = colonne;
    *nbLigne = max;
    *nbChar = nbUn;
    
}

int** init_tab(int l, int c){
    int **tab = malloc(l * sizeof(int*));
    for (int i = 0; i < l; i++) {
        tab[i] = malloc(c * sizeof(int));
    } 
    
    return tab;
}

void fill_tab(int ** tab, char path[]){
    char entry;
    FILE* f;
    f = fopen(path, "r");
    entry = fgetc(f);
    int i = 0, j = 0;
    while(entry != EOF)
    {
        if (entry != '\n')
        {
            tab[i][j] = entry-48;
            j++;
        }
        else
        {
            i++;
            j=0;
        }
        entry = fgetc(f);
    }
}

void reading(char map[], SDL_Rect* r, chp_t* c) {
    
    int nbCol = 0;
    int nbLigne= 0;
    int nbUn;
    tailleFichier(&nbCol, &nbLigne, &nbUn, map);

    int** tab = init_tab(nbLigne, nbCol);
    
    fill_tab(tab, map);
    //printf("%d", nbCol);
    //printf("%d", nbLigne);
    
    //SDL_Rect destRect;
    int pos =0;
    int posx = 0;
    int poys = 0;
        //destRect.w = 32; 
        //destRect.h = 32; 

    for (int i = 0; i < nbLigne; i++)
    {
        for (int j = 0; j < nbCol; j++)
        {
            //destRect.x = j * destRect.w;
            //destRect.y = i * destRect.h;
            posx = j*32;
            poys = i*32;
            switch (tab[i][j]){
                case 1:
                    //SDL_RenderCopy(renderer, texture, NULL, &destRect);
                    r[pos].h =32;
                    r[pos].w =32;
                    r[pos].x = posx;
                    r[pos].y = poys-720;
                    pos++;

                    break;
                case 2:
                    c->posX = posx;
                    c->posY = poys-720;
                    //SDL_RenderCopy(renderer, c, NULL, &destRect);
                    break;
                default:
                    break;
            }

        }
        // printf("\n");
    }

    for (int i = 0; i < nbLigne; i++) {
    free(tab[i]);
    }
    free(tab);
    //SDL_DestroyTexture(texture);
}

