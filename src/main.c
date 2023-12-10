#include "image.h"
#include "menu.h"
#include "reader.h"
#include "credit.h"
#include "jeu.h"
#include "player.h"
#include "collision.h"
#include <stdbool.h>
#include "enemy.h"
#include "fight.h"

int main()
{
    
    int nbCol = 0;
    int nbLigne= 0;
    int nbUn= 0;
    int nbEnemies = 0;
    char map[15] = "src/map.txt";
    tailleFichier(&nbCol, &nbEnemies, &nbUn, "src/enemies.txt");
    nbEnemies;
    enemy_t * e[nbEnemies];
    enemy_t * chain = malloc(sizeof(enemy_t));

    chain->hp = NULL; 
    chain->posX = NULL;
    chain->posY = NULL;
    chain->next = NULL;
    readEnemyList(chain, "src/enemies.txt");
    // for (int i = 0; i < nbEnemies; i++)
    // {
    //     e[i] = malloc(sizeof(enemy_t));
    
    // }
    // readEnemy(e, "src/enemies.txt");


    SDL_Rect enemies[nbEnemies];

    printf("%d, %d, %d\n", chain->hp, chain->posX, chain->posY);    
    printf("%d, %d, %d\n", chain->next->hp, chain->next->posX, chain->next->posY);
    printf("%d, %d, %d\n", chain->next->next->hp, chain->next->next->posX, chain->next->next->posY);



    // printf("%d, %d, %d\n", e[0]->hp, e[0]->posX, e[0]->posY);
    // printf("%d, %d, %d\n", e[1]->hp, e[1]->posX, e[1]->posY);
    // printf("%d, %d, %d\n", e[2]->hp, e[2]->posX, e[2]->posY);
    //return 0;

    nbCol = 0;
    nbUn= 0;
    tailleFichier(&nbCol, &nbLigne, &nbUn, map);
    //printf("%d", nbUn);
    // //printf("%d %d", nbCol, nbLigne);

    // int** tab = init_tab(nbLigne, nbCol);
    // fill_tab(tab);
    // for (int i = 0; i < nbLigne; i++)
    // {
    //     for (int j = 0; j < nbCol; j++)
    //     {
    //         printf("%d", tab[i][j]);
    //     }        
    //     printf("\n");
    // }

    SDL_Window *window = NULL;
    int statut = EXIT_FAILURE;

    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());

        return EXIT_FAILURE;
    }
    window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_RESIZABLE);
    if(NULL == window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        return EXIT_FAILURE;
    }
    /* On agit sur la fenêtre ici */
    SDL_Renderer* ecran;

    menu_t* m = malloc(sizeof(menu_t));

    credit_t* c = malloc(sizeof(credit_t));

    jeu_t* game = malloc(sizeof(jeu_t));

    player_t* p = malloc(sizeof(player_t));

    chp_t* chkp = malloc(sizeof(chp_t));

    //enemy_t * e = malloc(sizeof(enemy_t));
    
    
    //e[1]->hp = 70;
    //printf("HP enemy 1 : %d", e->hp);

    initPlayer(p, 1280-640, 720-360);

    CollisionType collisionType;
    CollisionType collisionType2;

    c->state = -1;

    game->state = -1;

    SDL_Rect destR[nbCol*nbLigne];

    SDL_Rect play;

    SDL_Rect cp;
    cp.h = 32;
    cp.w = 32;
    cp.x = 0;
    cp.y = 0;

    Uint32 lastTime = SDL_GetTicks();
    float deltaTime;
    Uint32 currentTime = SDL_GetTicks();

    deltaTime = (float)(currentTime - lastTime) / SDL_GetPerformanceFrequency();
    //printf("%d", c->state);

    ecran = init_renderer(window, m);

    bool terminer = false;
    
    SDL_Texture* enemy = charger_image("src/enemy.bmp", ecran);
    if (enemy == NULL) {
    fprintf(stderr, "Erreur chargement texture : %s", SDL_GetError());
    }

    SDL_Texture* joueur = charger_image("src/player.bmp", ecran);
    if (joueur == NULL) {
    fprintf(stderr, "Erreur chargement texture : %s", SDL_GetError());
    }

    SDL_Texture* terrain = charger_image("src/terrain.bmp", ecran);
    if (terrain == NULL) {
    fprintf(stderr, "Erreur chargement texture : %s", SDL_GetError());
    }
    SDL_Texture* checkpoint = charger_image_transparente("src/end.bmp", ecran, 255, 255, 255);
    if (checkpoint == NULL) {
    fprintf(stderr, "Erreur chargement texture : %s", SDL_GetError());
    }
    reading(map, destR, chkp);
    cp.x = chkp->posX;
    cp.y = chkp->posY;
    printf("TRUC MERDE %d, %d, %d, %d\n", cp.h, cp.w, cp.x, cp.y);
    SDL_Event evenements;
    int i = 0; //mx=0, my=0;
    bool r = false;
    bool l = false;
    bool s = false;
    prepare_enemies_list(enemies, chain, nbEnemies);

    while(!terminer){
        //currentTime = SDL_GetTicks();

        if (m->state == 0)
        {
            refresh_menu(ecran, m);
        }
        //printf("%d", m->state);
        if (m->state == 2 && c->state == -1)
        {
            ecran = init_credit(c, ecran);
        }
        if (m->state == 1 && game->state == -1)
        {
            ecran = init_jeu(game, ecran, p);
        }
        
        if (c->state == 0)
        {
            refresh_credit(ecran, c);
        }
        if (c->state == 1)
        {
            back2menu(m, ecran);
            c->state = -1;
        }
        if (game->state == 0)
        {
            refresh_jeu(ecran, game, terrain, checkpoint, map, destR, nbUn, &play, &cp ,joueur);
            print_enemies(enemies, nbEnemies, ecran, enemy);
            //SDL_RenderCopy(ecran, checkpoint, NULL, &cp);
            
            SDL_RenderPresent(ecran);
        }
        if (game->state == 1)
        {
            back2menu(m, ecran);
            game->state = -1;
        }

        i = i+1;
        currentTime = SDL_GetTicks();
        deltaTime = (float)(currentTime - lastTime) / 1000.0f;
        collisionType = collisions(p, destR, nbUn);
        for(int i = 0; i < nbEnemies; i++)
        {
            collisionType2 = collisionsEnemy(enemies[i], destR, nbUn);
             if(collisionType2 != TOP_COLLISION)
             {
                
                enemies[i].y += (100- p->velocity) * deltaTime;
             }
        }
       
        int machin;
        //GRAVITY
        if((collisionType == NO_COLLISION) || (p->is_jumping && p->timer > 0) || (collisionType == BOTTOM_COLLISION))
        {
            gravity(destR, nbUn, deltaTime, p);
            // for (int i = 0; i < nbEnemies; i++){
            //         enemies[i].y += (100- p->velocity) * deltaTime;
            //     }
            if (p->is_jumping == 0)
            {
                cp.y -= (100- p->velocity) * deltaTime;
                for (int i = 0; i < nbEnemies; i++){
                        enemies[i].y -= (100- p->velocity) * deltaTime;
                 }
            }
            
                                    //;
            if(p->is_jumping) 
            {
                cp.y -= (100- p->velocity) * deltaTime;
                for (int i = 0; i < nbEnemies; i++){
                        enemies[i].y -= (100- p->velocity) * deltaTime;
                 }
                    p->timer -= 1;
                    if(p->timer <= 0)
                    {
                        p->is_jumping = 0;
                        p->velocity = 0;
                        machin = 0;
                    }
                    if(collisionType == BOTTOM_COLLISION)
                    {
                        p->is_jumping = 0;
                        p->velocity = 0;
                    }
             }
        }
        if(collisionType == TOP_COLLISION)
        {
            p->timer = 20;
            machin = 0;
            p->nbJump = 0;
        }
        if ((p->posX - cp.x <= abs(32)) && (p->posY - cp.y <= abs(32)))
        {
                strcpy(map, "src/mapp.txt");
                        
                        tailleFichier(&nbLigne, &nbCol, &nbUn, map);
                        reading(map, destR, chkp);
                        cp.x = chkp->posX;
                        cp.y = chkp->posY;
        }
        
        // Detection collision avec un ennemi 
        for (int i = 0; i < nbEnemies; i++) {
        if (playerEnemyCollision(p, enemies[i]) && !p->isFighting) {
            //printf("HP : %d \n", e[i+1]->hp);
            p->isFighting = 1;
            printf("Player collided with enemy %d\n", i);
            startCombat(ecran, p, e[i+1]);

            }
        }

        lastTime = currentTime;
        SDL_PollEvent( &evenements );
        if (m->state == 0)
        {
            handle_menu(&evenements, m);
        }
        if (c->state == 0 && m->state == 2)
        {
            handle_credit(&evenements, c);
        }
        if ((game->state == 0 && m->state == 1))
        {
                switch(evenements.type)
                {  
                    case SDL_KEYDOWN:
                        switch(evenements.key.keysym.sym)
                        {
                            case SDLK_p:
                                game->state = 1;
                                break;
                        }
                }
        }
        switch(evenements.type)
        {

            case SDL_QUIT:
                terminer = true; 
                break;
            
            case SDL_KEYDOWN:
                switch(evenements.key.keysym.sym)
                {
                    case SDLK_p:
                        game->state = 1;
                        break;
                    case SDLK_0:
                        strcpy(map, "src/mapp.txt");
                        
                        tailleFichier(&nbLigne, &nbCol, &nbUn, map);
                        reading(map, destR, chkp);

                        printf("%d", nbUn);
                        break;
                    case SDLK_ESCAPE:
                        case SDLK_q:
                            terminer = true; 
                            break;
                        break;
                    break;
                }  
        }
        if ((game->state == 0 && m->state == 1))
        {        
            if (evenements.type == SDL_KEYDOWN)
            {
                switch (evenements.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    r = true;
                    break;
                case SDLK_LEFT:
                    l = true;
                    break;
                case SDLK_SPACE:
                    s = true;
                    break;
                default:
                    break;
                }
            }
            if (evenements.type == SDL_KEYUP)
            {
                switch (evenements.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    r = false;
                    break;
                case SDLK_LEFT:
                    l = false;
                    break;
                case SDLK_SPACE:
                    p->nbJump++;
                    printf("%d\n", p->nbJump);
                    if(p->nbJump < p->nbJumpCan)
                    {
                        machin = 1;
                        p->timer = 20;
                    }else
                    {
                        machin = 0;
                    }
                    s = false;
                    break;
                default:
                    break;
                }
            }
            // DEPLACEMENT DU JOUEUR
            // right
            if (r && !p->isFighting){                
                collisionType = collisions(p, destR, nbUn);
                if(collisionType != LEFT_COLLISION && collisionType != SAD_COLLISION){
                    cp.x = cp.x - (185 * deltaTime);
                    for(int i = 0; i < nbUn; i++){
                        destR[i].x = destR[i].x-(185 * deltaTime);
                    }
                    for (int i = 0; i < nbEnemies; i++){
                            enemies[i].x = enemies[i].x-(185 * deltaTime);
                        }
                }else
                {
                    switch (collisionType){
                        case LEFT_COLLISION:
                            cp.x = cp.x +6;
                            for (int i = 0; i < nbEnemies; i++){
                                enemies[i].x = enemies[i].x+6;
                            }
                            for(int i = 0; i < nbUn; i++){
                                destR[i].x = destR[i].x+6;
                            }
                            break;
                        case SAD_COLLISION:
                            cp.x = cp.x +6;
                            for (int i = 0; i < nbEnemies; i++){
                                enemies[i].x = enemies[i].x+6;
                            }
                            for(int i = 0; i < nbUn; i++){
                                destR[i].x = destR[i].x+6;
                            }
                        default:
                            break;
                    }
                    
                }
            }
            // left
            if (l && !p->isFighting){
                collisionType = collisions(p, destR, nbUn);
                if(collisionType != RIGHT_COLLISION && collisionType != SAD_COLLISION){
                        cp.x = cp.x + (200 * deltaTime);
                        for (int i = 0; i < nbEnemies; i++){
                            enemies[i].x = enemies[i].x+(200 * deltaTime);
                        }  
                        for(int i = 0; i < nbUn; i++){
                        destR[i].x = destR[i].x+(200 * deltaTime);
                        }
                }else
                {
                    switch (collisionType){
                        case RIGHT_COLLISION:
                            cp.x = cp.x -6;
                            for (int i = 0; i < nbEnemies; i++){
                                enemies[i].x = enemies[i].x-6;
                            }
                            for(int i = 0; i < nbUn; i++){
                                destR[i].x = destR[i].x-6;
                            }
                            break;
                        case SAD_COLLISION:
                            cp.x = cp.x -6;
                            for (int i = 0; i < nbEnemies; i++){
                                enemies[i].x = enemies[i].x-6;
                            }
                            for(int i = 0; i < nbUn; i++){
                                destR[i].x = destR[i].x-6;
                            }
                        default:
                            break;
                    }
                }
            }  
            // jump
            if (s && !p->isFighting){
                collisionType = collisions(p, destR, nbUn);
                if(collisionType == TOP_COLLISION || machin){
                    p->is_jumping = 1;
                    p->velocity = 300;
                }
            }else {
                    p->velocity = 0;
                    p->is_jumping = 0;
            }
        }
        SDL_Delay(20);
    }
    statut = EXIT_SUCCESS;
    // SDL_DestroyTexture(fond);
    free_menu(m);
    free_jeu(game);
    free_credit(c);
    SDL_DestroyRenderer(ecran);
    SDL_DestroyWindow(window);
    //Quit:
    SDL_Quit();
    return statut;
}