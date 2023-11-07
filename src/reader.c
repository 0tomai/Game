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
        taille ++;
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
    fclose(f);
    max = max-1;
    colone = colone-1;
    *nbCol = colone;
    *maxLigne = max;
}




int main(int argc, char const *argv[])
    {
        int** tab = remplirTableau(5, 5);
        
        return 0;
    }
