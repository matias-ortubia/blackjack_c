#include <stdlib.h>
#include <stdio.h>

#include "../inc/blackjack.h"
#include "../inc/deck.h"

struct blackjack {
    player_t **players;
    deck_t *deck;
    size_t players_qty;
    bool is_game_over;
};

blackjack_t *blackjack_new_game(player_t **players, size_t players_qty, deck_t *deck) {
    blackjack_t *blackjack = malloc(sizeof(blackjack_t));
    if(blackjack == NULL) return NULL;

    blackjack->players = players;
    blackjack->deck = deck;
    blackjack->players_qty = players_qty;
    blackjack->is_game_over = false;

    return blackjack;
}

void blackjack_destroy(blackjack_t *blackjack) {
    free(blackjack);
}

size_t _count_still_playing(blackjack_t *blackjack) {
    size_t counter = 0;
    for(size_t i = 0; i < blackjack->players_qty; i++) {
        if (player_is_still_playing(blackjack->players[i]))
            counter++;
    }
    return counter;
}

bool _check_already_won(player_t *player, blackjack_t *blackjack) {
    if (player_get_points(player) == 21) return true;
    for (size_t i = 0; i < blackjack->players_qty; i++) {
        unsigned int temp_player_points = player_get_points(blackjack->players[i]);
        if (temp_player_points >= player_get_points(player) &&
            temp_player_points <= 21 && player != blackjack->players[i]) {
            return false;
        }
    }
    return true;
}

player_t *_get_still_playing(blackjack_t *blackjack) {
    player_t *player_still_playing;
    for(size_t i = 0; i < blackjack->players_qty; i++) {
        player_t *temp_player = blackjack->players[i];
        if (player_is_still_playing(temp_player))
            player_still_playing = temp_player;
    }
    return player_still_playing;
}

bool _check_game_over(blackjack_t *blackjack) {
    unsigned int players_playing = _count_still_playing(blackjack);
    if (players_playing == 0) return true;
    else if (players_playing == 1) {
        player_t *player_playing = _get_still_playing(blackjack);
        if (_check_already_won(player_playing, blackjack)) return true;
    }
    return false;
}

// NULL == DRAW
player_t *_get_winner(blackjack_t *blackjack) {
    player_t *prev_winner;
    player_t *winner;

    if (blackjack->players[0] > blackjack->players[1]) {
        winner = blackjack->players[0];
        prev_winner = blackjack->players[1];
    }
    else {
        winner = blackjack->players[1];
        prev_winner = blackjack->players[0];
    }

    for(size_t i = 0; i < blackjack->players_qty; i++) {
        unsigned int temp_player_points = player_get_points(blackjack->players[i]);
        if (temp_player_points <= 21 && 
            temp_player_points > player_get_points(winner)) {
            prev_winner = winner;
            winner = blackjack->players[i];
        }
    }

    if (player_get_points(prev_winner) == player_get_points(winner)) 
        return NULL;
    if (player_get_points(winner) > 21) {
        if (player_get_points(prev_winner) > 21)
            return NULL;
        else return prev_winner;
    }
    else return winner;
}

void _clean_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int _get_option(char *msg) {
    printf("%s", msg);
    
    int c = getchar();
    while (c == '\n') {
        printf("%s", msg);
        c = getchar(); 
    }

    _clean_buffer();

    return c;
}

bool _initial_turn(player_t *player, deck_t *deck) {
    card_t *card_taken = player_take_card(player, deck);
    if (card_taken == NULL) return false;

    printf("Player %d picked ", player_get_num(player));
    card_show(card_taken);

    return true;
}

bool _turn(player_t *player, deck_t *deck) {
    printf("\nPlayer %u turn.\t%u points.\n", player_get_num(player), 
                                            player_get_points(player));
    int c = _get_option("Pick a card? Y/N: ");
    while (c != 'Y' && c != 'y' && c != 'N' && c != 'n')
        c = _get_option("Pick a card? Y/N: ");

    if (c == 'Y' || c == 'y') {
        card_t *card_taken = player_take_card(player, deck);
        if (card_taken == NULL) return false;

        printf("Player %u picked ", player_get_num(player)); 
        card_show(card_taken);
    }

    else player_set_still_playing(player, false);

    return true;
}

void blackjack_show_all_points(blackjack_t *blackjack) {
    for (size_t i = 0; i < blackjack->players_qty; i++) {
        player_t *temp_player = blackjack->players[i];
        printf("\nPlayer %u: %d points.\n", player_get_num(temp_player), 
                                    player_get_points(temp_player));
    }
}

void blackjack_show_winner(player_t *winner) {
    if (winner == NULL) printf("\nIt's a draw!\n");
    else printf("\nWinner: Player %d!\n", player_get_num(winner));
}

bool blackjack_start(blackjack_t *blackjack) {
    deck_shuffle(blackjack->deck);

    for (size_t i = 0; i < blackjack->players_qty; i++)
        if (_initial_turn(blackjack->players[i], blackjack->deck) == false)
            return false;

    while (blackjack->is_game_over == false) {
        for (size_t i = 0; i < blackjack->players_qty; i++) {
            player_t *player = blackjack->players[i];

            if (player_is_still_playing(player)) {
                if (_turn(player, blackjack->deck) == false) return false;

                if (player_get_points(player) >= 21) 
                    player_set_still_playing(player, false);
            }

            if (_check_game_over(blackjack) == true) {
                blackjack->is_game_over = true;
                break;
            }
        }
    }

    blackjack_show_all_points(blackjack);
    blackjack_show_winner(_get_winner(blackjack));

    return true;
}
