#include <stdio.h>

#include "../inc/card.h"
#include "../inc/deck.h"
#include "../inc/player.h"

//#define SHUFFLE_TEST
#define PLAYER_TEST

int main(void) {
    deck_t *deck = deck_construct();
    if (deck == NULL) return 1;

    player_t *player1 = player_construct();
    if (player1 == NULL) return 1;
#ifdef SHOW_DECK_TEST
    deck_show(deck);
#endif
#ifdef POP_PUSH_TEST
    card_t *card_taken = deck_pop(deck);
    printf("\nCarta tomada: ");
    card_show(card_taken);

    printf("\nAhora se vuelve a mostrar el deck\n");
    deck_show(deck);


    printf("\nSe devuelve la carta al mazo\n");
    deck_push(deck, card_taken);

    printf("\nMuestra el mazo de nuevo:\n");
    deck_show(deck);
#endif
#ifdef PEEK_TEST
    printf("\nPeek: ");
    card_show(deck_peek(deck));
#endif
#ifdef POP_UNTIL_EMPTY_TEST
    while(!deck_is_empty(deck)) deck_pop(deck);
    printf("%s", deck_is_empty(deck) ? "si" : "no");
#endif
#ifdef SHUFFLE_TEST
    deck_show(deck);
    deck_shuffle(deck);

    printf("\nSe muestra el mazo de nuevo:\n");
    deck_show(deck);
#endif
#ifdef PLAYER_TEST
    player_take_card(player1, deck);
    player_take_card(player1, deck);
    player_take_card(player1, deck);

    player_show_hand(player1);
    deck_show(deck);

    printf("%u", player_get_points(player1));
#endif

    deck_destroy(deck);
    player_destroy(player1);
    return 0;
}
