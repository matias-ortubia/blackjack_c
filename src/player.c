#include <stdlib.h>

#include "../inc/player.h"

struct player {
    card_t **hand;
    size_t cards_in_hand;
    unsigned int points;
    unsigned int wins;
    unsigned int loses;
};

player_t *player_construct() {
    player_t *player = malloc(sizeof(player_t));
    if (player == NULL) return NULL;

    player->hand = malloc(sizeof(card_t *));
    if (player->hand == NULL) {
        free(player);
        return NULL;
    }

    player->cards_in_hand = 0;
    player->points = 0;
    player->wins = 0;
    player->loses = 0;

    return player;
}

void player_destroy(player_t *player) {
    for (size_t i = 0; i < player->cards_in_hand; i++) {
        card_destroy(player->hand[i]);
    }
    free(player);
}

unsigned int player_get_points(player_t *player);
unsigned int player_get_wins(player_t *player);
unsigned int player_get_loses(player_t *player);

card_t *player_take_card(player_t *player, deck_t *deck) {
    card_t **temp_hand = realloc(player->hand, sizeof(card_t *) * (player->cards_in_hand + 1));
    if (temp_hand == NULL) return NULL;

    player->hand = temp_hand;
    card_t *card_taken = deck_pop(deck);
    player->hand[player->cards_in_hand] = card_taken;
    player->cards_in_hand++;

    return card_taken;
}

unsigned int player_sum_points(player_t *player);

void player_show_hand(player_t *player) {
    for (size_t i = 0; i < player->cards_in_hand; i++) {
        card_show(player->hand[i]);
    }
}
