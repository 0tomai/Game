#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "reader.h"
#include "image.h"


void tailleFichier(int* nbLigne, int* nbCol)
{
    int taille = 0;
    int max = 0;
    int colonne = 0;
    char c;
    FILE* f;
    f = fopen("src/map.txt", "r");
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
}

int** init_tab(int l, int c){
    int **tab = malloc(l * sizeof(int*));
    for (int i = 0; i < l; i++) {
        tab[i] = malloc(c * sizeof(int));
    } 
    
    return tab;
}

void fill_tab(int ** tab){
    char entry;
    FILE* f;
    f = fopen("src/map.txt", "r");
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