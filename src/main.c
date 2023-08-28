#include <stdio.h>

#include "../inc/card.h"
#include "../inc/deck.h"
#include "../inc/player.h"

int get_option(char *msg);

int main(void) {
    deck_t *deck = deck_construct();
    if (deck == NULL) return 1;

    player_t *player1 = player_construct(1);
    player_t *player2 = player_construct(2);
    if (player1 == NULL || player2 == NULL) return 1;

    deck_shuffle(deck);

    card_t *card_taken = player_take_card(player1, deck);
    printf("Player %d picked ", player_get_num(player1));
    card_show(card_taken);

    card_taken = player_take_card(player2, deck);
    printf("Player %d picked ", player_get_num(player2));
    card_show(card_taken);

    while (player_get_points(player1) <= 21 && 
           player_get_points(player2) <= 21 && 
          (player_is_still_playing(player1) || 
           player_is_still_playing(player2))) {

        if (player_is_still_playing(player1)) {
            printf("\nPlayer %u turn.\t%u points.\n", player_get_num(player1), 
                                                    player_get_points(player1));
            int c = get_option("Pick a card? Y/N: ");
            while (c != 'Y' && c != 'y' && c != 'N' && c != 'n')
                c = get_option("Pick a card? S/N:  ");

            if (c == 'Y' || c == 'y') {
                card_taken = player_take_card(player1, deck);
                printf("Player %u picked ", player_get_num(player1)); 
                card_show(card_taken);

                if (player_get_points(player1) >= 21)
                    break;
            
            } else {
                player_set_still_playing(player1, false);
                if (player_get_points(player2) > player_get_points(player1))
                    break;
            }
        }

        if (player_is_still_playing(player2)) {
            printf("\nPlayer %u turn.\t%u points.\n", player_get_num(player2), 
                                                    player_get_points(player2));
            int c = get_option("Pick a card? Y/N: ");
            while (c != 'Y' && c != 'y' && c != 'N' && c != 'n')
                c = get_option("Pick a card? Y/N  ");

            if (c == 'Y' || c == 'y') {
                card_taken = player_take_card(player2, deck);
                printf("Player %u picked ", player_get_num(player2)); 
                card_show(card_taken);

                if (player_get_points(player2) >= 21)
                    break;
            
            } else {
                player_set_still_playing(player2, false);
                if (player_get_points(player1) > player_get_points(player2))
                    break;
            }
        }

        if (player_is_still_playing(player1) == false && 
            player_get_points(player2) > player_get_points(player1))
            break;

        if (player_is_still_playing(player2) == false && 
            player_get_points(player1) > player_get_points(player2))
            break;
    }

    unsigned int points_player1 = player_get_points(player1);
    unsigned int points_player2 = player_get_points(player2);

    printf("\nPlayer 1: %d\n", points_player1);
    printf("Player 2: %d\n", points_player2);

    player_t *winner = NULL;
    if (points_player1 > 21) winner = player2;

    else if (points_player2 > 21) winner = player1;

    else if (points_player1 > points_player2) winner = player1;

    else if (points_player2 > points_player1) winner = player2;

    if (winner == NULL) printf("It's a draw!\n");
    else printf("\nWinner: Player %d.\n", player_get_num(winner));

    deck_destroy(deck);
    player_destroy(player1);
    player_destroy(player2);
    return 0;
}

int get_option(char *msg) {
    printf("%s", msg);
    
    int c = getchar();
    while (c == '\n') {
        printf("%s", msg);
        c = getchar(); 
    }
    while (getchar() != '\n');

    return c;
}
