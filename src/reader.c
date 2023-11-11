#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include "reader.h"
#include "image.h"
//fontion taille fichier

int** remplirTableau(int l, int c){
    int **tab = malloc(l * sizeof(int*));
    for (int i = 0; i < l; i++) {
        tab[i] = malloc(c * sizeof(int));
    } 
    return tab;
}


void tailleFichier(int* nbCol, int* maxLigne)
{
    int taille = 0;
    int max = 0;
    int colone = 0;
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
            colone ++;
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
        colone ++;
            if(max < taille)
            {
                max = taille;
            }
    }
    
    max = max;
    colone = colone;
    *nbCol = colone;
    *maxLigne = max;
}
