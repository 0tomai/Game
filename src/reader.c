#include "reader.h"


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

void reading(SDL_Renderer* renderer) {
    
    int nbCol = 0;
    int nbLigne= 0;
    tailleFichier(&nbCol, &nbLigne);

    int** tab = init_tab(nbLigne, nbCol);
    fill_tab(tab);
    //printf("%d", nbCol);
    //printf("%d", nbLigne);
    SDL_Texture* texture = charger_image("src/terrain.bmp", renderer);
    if (texture == NULL) {
    fprintf(stderr, "Erreur chargement texture : %s", SDL_GetError());
    }
    SDL_Rect destRect;
        destRect.w = 16; 
        destRect.h = 16; 

    for (int i = 0; i < nbLigne; i++)
    {
        for (int j = 0; j < nbCol; j++)
        {
            destRect.x = j * destRect.w;
            destRect.y = i * destRect.h;

            switch (tab[i][j]){
                case 1:
                    SDL_RenderCopy(renderer, texture, NULL, &destRect);
                    break;
                case 2:
                    //printf("%d", tab[i][j]);
                    break;
                default:
            }
        }
        // printf("\n");
    }

    for (int i = 0; i < nbLigne; i++) {
    free(tab[i]);
    }
    free(tab);
    SDL_DestroyTexture(texture);
}

