#include <stdlib.h>

#include "../inc/player.h"

struct player {
    card_t **hand;
    size_t cards_in_hand;
    unsigned int num;
    unsigned int points;
    unsigned int wins;
    unsigned int loses;
    bool is_still_playing;
};

player_t *player_construct(unsigned int num) {
    player_t *player = malloc(sizeof(player_t));
    if (player == NULL) return NULL;

    player->hand = malloc(sizeof(card_t *));
    if (player->hand == NULL) {
        free(player);
        return NULL;
    }

    player->num = num;
    player->cards_in_hand = 0;
    player->points = 0;
    player->wins = 0;
    player->loses = 0;
    player->is_still_playing = true;

    return player;
}

void player_destroy(player_t *player) {
    for (size_t i = 0; i < player->cards_in_hand; i++) {
        card_destroy(player->hand[i]);
    }
    free(player);
}

unsigned int player_get_num(player_t *player) {
    return player->num;
}

unsigned int player_get_points(player_t *player) {
    return player->points;
}

unsigned int player_get_wins(player_t *player);
unsigned int player_get_loses(player_t *player);

bool player_is_still_playing(player_t *player) {
    return player->is_still_playing;
}

void player_set_still_playing(player_t *player, bool still_playing) {
    player->is_still_playing = still_playing;
}

card_t *player_take_card(player_t *player, deck_t *deck) {
    if (deck_is_empty(deck)) return NULL;

    card_t **temp_hand = realloc(player->hand, sizeof(card_t *) * (player->cards_in_hand + 1));
    if (temp_hand == NULL) return NULL;

    player->hand = temp_hand;
    card_t *card_taken = deck_pop(deck);
    player->hand[player->cards_in_hand] = card_taken;
    player->cards_in_hand++;

    unsigned int card_taken_value = card_get_number(card_taken);
    if (card_taken_value == 11 || card_taken_value == 12 || card_taken_value == 13)
        card_taken_value = 10;
    else if (card_taken_value == 1) {
        if (player->points + 11 < 21)
            card_taken_value = 11;
    }
    player->points += card_taken_value;

    return card_taken;
}

void player_show_hand(player_t *player) {
    for (size_t i = 0; i < player->cards_in_hand; i++) {
        card_show(player->hand[i]);
    }
}
