#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "../inc/blackjack.h"
#include "../inc/card.h"
#include "../inc/deck.h"
#include "../inc/player.h"

int main(void) {
    deck_t *deck = deck_construct();
    if (deck == NULL) return 1;

    player_t *player1 = player_construct(1);
    player_t *player2 = player_construct(2);
    if (player1 == NULL || player2 == NULL) {
        deck_destroy(deck);
        return 1;
    }

    player_t *players[2] = {player1, player2};

    deck_shuffle(deck);

    blackjack_t *game = blackjack_new_game(players, 2, deck);
    if (game == NULL) {
        player_destroy(player1);
        player_destroy(player2);
        deck_destroy(deck);
        return 1;
    }

    if (blackjack_start(game) == false) {
        printf("%s. Error code: %d", strerror(errno), errno);
    }

    deck_destroy(deck);
    player_destroy(player1);
    player_destroy(player2);
    blackjack_destroy(game);

    return 0;
}
