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
    enemy_t * chain = malloc(sizeof(enemy_t));

    chain->hp = -1; 
    chain->posX = -1;
    chain->posY = -1;
    chain->next = NULL;
    readEnemyList(chain, "src/enemies.txt");

    SDL_Rect enemies[nbEnemies];

    nbCol = 0;
    nbUn= 0;
    tailleFichier(&nbCol, &nbLigne, &nbUn, map);

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
    
    //Allocation des differents elements du jeu
    SDL_Renderer* ecran;

    menu_t* m = malloc(sizeof(menu_t));

    credit_t* c = malloc(sizeof(credit_t));

    jeu_t* game = malloc(sizeof(jeu_t));

    player_t* p = malloc(sizeof(player_t));

    chp_t* chkp = malloc(sizeof(chp_t));

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


    //Permet d'avoir un deplacement fluide et non en crénaux
    deltaTime = (float)(currentTime - lastTime) / SDL_GetPerformanceFrequency();

    ecran = init_renderer(window, m);

    bool terminer = false;
    
    //init de chaque texture necessaire au jeu
    SDL_Texture* enemy = charger_image("src/enemy.bmp", ecran);
    if (enemy == NULL) {
    fprintf(stderr, "Erreur chargement texture : %s", SDL_GetError());
    }

    SDL_Texture* joueur = charger_image("src/player2.bmp", ecran);
    if (joueur == NULL) {
    fprintf(stderr, "Erreur chargement texture : %s", SDL_GetError());
    }

    SDL_Texture* terrain = charger_image("src/terrain2.bmp", ecran);
    if (terrain == NULL) {
    fprintf(stderr, "Erreur chargement texture : %s", SDL_GetError());
    }
    SDL_Texture* checkpoint = charger_image_transparente("src/end.bmp", ecran, 255, 255, 255);
    if (checkpoint == NULL) {
    fprintf(stderr, "Erreur chargement texture : %s", SDL_GetError());
    }
    SDL_Texture* fin = charger_image("src/win.bmp", ecran);
    if (checkpoint == NULL) {
    fprintf(stderr, "Erreur chargement texture : %s", SDL_GetError());
    }

    reading(map, destR, chkp);
    cp.x = chkp->posX;
    cp.y = chkp->posY;
    SDL_Event evenements;
    int i = 0;
    bool r = false;
    bool l = false;
    bool s = false;
    int map_num = 0;
    int nbEnemiesKilled = 0;
    prepare_enemies_list(enemies, chain, nbEnemies);

    while(!terminer){

        // Gestion des differents etats du menu, des credits et du jeu
        if (m->state == 0) //On est sur le menu
        {
            refresh_menu(ecran, m);
        }
        
        if (m->state == 2 && c->state == -1) //Init des credits
        {
            ecran = init_credit(c, ecran);
        }

        if (m->state == 1 && game->state == -1) //Init du jeu
        {
            ecran = init_jeu(game, ecran, p);
        }
        
        if (c->state == 0) //On rentre dans les crédits
        {
            refresh_credit(ecran, c);
        }
        if (c->state == 1) //Quitter les crédits
        {
            back2menu(m, ecran);
            c->state = -1;
        }
        if (game->state == 0) //Le jeu est en cours
        {
            refresh_jeu(ecran, game, terrain, checkpoint, destR, nbUn, &play, &cp ,joueur);
            print_enemies(enemies, nbEnemies, ecran, enemy);            
            SDL_RenderPresent(ecran);
        }
        if (game->state == 1) //On met le jeu en pause pour revenir au menu
        {
            back2menu(m, ecran);
            game->state = -1;
        }
        // Game Over
        if (game->state == 2)
        {
            renderGameOverText(ecran);
        }

        i = i+1;
        currentTime = SDL_GetTicks();
        deltaTime = (float)(currentTime - lastTime) / 1000.0f;
        collisionType = collisions(p, destR, nbUn);

        for(int i = 0; i < nbEnemies; i++)
        {
            collisionType2 = collisionsEnemy(enemies[i], destR, nbUn);
             if(collisionType2 == NO_COLLISION && !p->is_jumping)
             {
                enemies[i].y += (100- p->velocity) * deltaTime;
             }
        }
       
        int machin;
        //GRAVITY
        if((collisionType == NO_COLLISION) || (p->is_jumping && p->timer > 0) || (collisionType == BOTTOM_COLLISION))
        {
            gravity(destR, nbUn, deltaTime, p);
            if (!p->is_jumping)
            {
                cp.y -= (100- p->velocity) * deltaTime;
                for (int i = 0; i < nbEnemies; i++){
                        enemies[i].y -= (100- p->velocity) * deltaTime;
                 }
            }
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

        if (((abs((int)p->posX - cp.x) <= 32) && (abs(p->posY - cp.y) <= 32)) && game->state == 0) //Test la position du joueur par rapport à l'arrivée
        {
            if (map_num < 1)
            {
                strcpy(map, "src/mapp.txt");        
                tailleFichier(&nbLigne, &nbCol, &nbUn, map);
                reading(map, destR, chkp);
                if (chain->next != NULL)
                {
                    chain->hp = -1;
                    chain->posX= -1;
                    chain->posY=-1;
                    free_list(chain->next);
                    chain->next = NULL;
                                
                }
                tailleFichier(&nbCol, &nbEnemies, &nbLigne, "src/enemies.txt");
                readEnemyList(chain, "src/enemies.txt");
                prepare_enemies_list(enemies, chain, nbEnemies);

                cp.x = chkp->posX;
                cp.y = chkp->posY;
                map_num++;
            }
            else
            {
                SDL_RenderCopy(ecran, fin, NULL, NULL);
                game->state = -2; // nouveau state pour restart le jeu
                SDL_RenderPresent(ecran);
            }
            
        }

        // Detection collision avec un ennemi 
        enemy_t * chainCopy = chain;
        for (int i = 0; i < nbEnemies; i++) {
        if (playerEnemyCollision(p, enemies[i]) && !p->isFighting && game->state == 0 && collisionType == TOP_COLLISION) {
            printf("HP : %d \n", chainCopy->hp);
            r = false;
            l = false;
            s = false;
            p->isFighting = 1;
            printf("Player collided with enemy %d\n", i);
            startCombat(ecran, p, chainCopy, &chain, enemies, &nbEnemies, i, game, enemy, joueur);
            nbEnemiesKilled++;
        }else {
            chainCopy = chain->next;
            }
        }
    

        lastTime = currentTime;

        //Gestion des evenements
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
                        if (game->state == -2 || game->state == 2)
                        {
                            if (game->state == 2)
                            {
                                nbEnemiesKilled--;
                            }
                            
                            strcpy(map, "src/map.txt");
                            tailleFichier(&nbLigne, &nbCol, &nbUn, map);
                            reading(map, destR, chkp);
                            tailleFichier(&nbCol, &nbEnemies, &nbLigne, "src/enemies.txt");
                            
                            if (chain->next != NULL)
                            {
                                chain->hp = -1;
                                chain->posX= -1;
                                chain->posY=-1;
                                free_list(chain->next);
                                
                                chain->next = NULL;
                            }
                            
                            readEnemyList(chain, "src/enemies.txt");
                            prepare_enemies_list(enemies, chain, nbEnemies);
                            p->hp = 1000;
                            cp.x = chkp->posX;
                            cp.y = chkp->posY;
                            map_num = 0;
                        }
                        
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
            // DEPLACEMENT DU JOUEUR et GESTION COLLISIONS
            // right
            if (r && !p->isFighting){                
                collisionType = collisions(p, destR, nbUn);
                if(collisionType != LEFT_COLLISION && collisionType != SAD_COLLISION){
                    cp.x = cp.x - (200 * deltaTime);
                    for(int i = 0; i < nbUn; i++){
                        destR[i].x = destR[i].x-(200 * deltaTime);
                    }
                    for (int i = 0; i < nbEnemies; i++){
                            enemies[i].x = enemies[i].x-(200 * deltaTime);
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
                if((collisionType == TOP_COLLISION || machin)&&(collisionType != BOTTOM_COLLISION)){
                    p->is_jumping = 1;
                    p->velocity = 300;
                }
            }else {
                    p->velocity = 0;
                    p->is_jumping = 0;
            }
        }
        SDL_Delay(33);
    }
    statut = EXIT_SUCCESS;
    write_killed_enemies("result.txt", nbEnemiesKilled);
    free_menu(m);
    free_jeu(game);
    free_credit(c);
    free(p);
    free(chkp);
    free_list(chain);
    SDL_DestroyTexture(checkpoint);
    SDL_DestroyTexture(enemy);
    SDL_DestroyTexture(terrain);
    SDL_DestroyTexture(joueur);
    SDL_DestroyRenderer(ecran);
    SDL_DestroyTexture(fin);
    SDL_DestroyWindow(window);
    //Quit:
    SDL_Quit();
    return statut;
}