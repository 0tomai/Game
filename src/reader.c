#include "reader.h"
#include <string.h>

//procedure qui compte le nombre de caractères maximum par ligne et le nombre de lignes, elle compte également le nombre de 1 pour connaitre le nombre d'elements de type mur à afficher
void tailleFichier(int* nbLigne, int* nbCol, int* nbChar, char path[])
{
    int taille = 0; //compte le nombre de 
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
    
    colonne = colonne;
    *nbCol = colonne;
    *nbLigne = max;
    *nbChar = nbUn;
    fclose(f);

}

//fonction qui initialise le tableau destiné à contenir les emplacements des 0 et 1 (vide et mur)
int** init_tab(int l, int c){
    int **tab = malloc(l * sizeof(int*));
    for (int i = 0; i < l; i++) {
        tab[i] = malloc(c * sizeof(int));
    } 
    
    return tab;
}

//procedure qui remplit 
void fill_tab(int ** tab, char path[]){
    char entry;
    FILE* f;
    f = fopen(path, "r");
    entry = fgetc(f);
    int i = 0, j = 0;
    while(entry != EOF) //on parcourt le fichier
    {
        if (entry != '\n') //si le caractère n'est pas un saut de ligne, on le stock dans le tableau
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
        fclose(f);

}

//procedure qui remplit un tableau de SDL_Rect en fonction du tableau d'entiers crée avec fill_tab
void reading(char map[], SDL_Rect* r, chp_t* c) {
    
    int nbCol = 0;
    int nbLigne= 0;
    int nbUn;
    tailleFichier(&nbCol, &nbLigne, &nbUn, map);

    int** tab = init_tab(nbLigne, nbCol);
    
    fill_tab(tab, map);

    int pos =0;
    int posx = 0;
    int poys = 0;


    for (int i = 0; i < nbLigne; i++)
    {
        for (int j = 0; j < nbCol; j++)
        {

            posx = j*32;
            poys = i*32;
            switch (tab[i][j]){
                case 1:
                    r[pos].h =32;
                    r[pos].w =32;
                    r[pos].x = posx;
                    r[pos].y = poys-720;
                    pos++;
                    break;

                case 2:
                    c->posX = posx;
                    c->posY = poys-720;
                    break;

                default:
                    break;
            }

        }
    }

    for (int i = 0; i < nbLigne; i++) {
    free(tab[i]);
    }
    free(tab);
}

