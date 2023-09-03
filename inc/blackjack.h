#ifndef BLACKJACK_H
#define BLACKJACK_H

#include "../inc/player.h"

typedef struct blackjack blackjack_t;

blackjack_t *blackjack_new_game(player_t **players, size_t players_qty, deck_t *deck);
void blackjack_destroy(blackjack_t *blackjack);

bool blackjack_start(blackjack_t *blackjack);

player_t *blackjack_get_winner(blackjack_t *blackjack); // NULL == DRAW

#endif
