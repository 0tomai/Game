#ifndef COMBAT_H
#define COMBAT_H

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "player.h"
#include "enemy.h"

typedef enum {
    COMBAT_IDLE,
    COMBAT_PLAYER_TURN,
    COMBAT_ENEMY_TURN,
    COMBAT_OVER
} CombatState;

void startCombat(SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t* head, SDL_Rect *enemies, int *nbEnemies, int index);
void renderCombatUI(SDL_Renderer *renderer, player_t *player, enemy_t *enemy);
void handlePlayerAttack(CombatState* combatState, SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t *head, SDL_Rect *enemies, int *nbEnemies, int index);
void handleEnemyAttack(CombatState* combatState, SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t *head, SDL_Rect *enemies, int *nbEnemies, int index);
bool isCombatOver(player_t *player, enemy_t *enemy);
void refresh_fight(CombatState* combatState, SDL_Renderer *renderer, player_t *player, enemy_t *enemy, enemy_t *head, SDL_Rect *enemies, int *nbEnemies, int index);

#endif // COMBAT_H
