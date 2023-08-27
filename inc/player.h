#ifndef PLAYER_H
#define PLAYER_H

#include "../inc/deck.h"

typedef struct player player_t;

player_t *player_construct();
void player_destroy(player_t *player);

unsigned int player_get_points(player_t *player);
unsigned int player_get_wins(player_t *player);
unsigned int player_get_loses(player_t *player);

card_t *player_take_card(player_t *player, deck_t *deck);
unsigned int player_sum_points(player_t *player);

void player_show_hand(player_t *player);

#endif
