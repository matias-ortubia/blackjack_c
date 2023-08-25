#include <stdio.h>
#include <stdlib.h>

#include "card.h"

struct card {
    unsigned int number;
    suit_t suit;
};

const char *suit_names[] = { "Hearts", "Diamonds", "Clovers", "Spades" };

card_t *card_construct(unsigned int number, suit_t suit) {
    card_t *card = malloc(sizeof(card_t));
    if (card == NULL) return NULL;

    card->number = number;
    card->suit = suit;

    return card;
}

void card_destroy(card_t *card) {
    free(card);
}

unsigned int card_get_number(card_t *card) {
    return card->number;
}

suit_t card_get_suit(card_t *card) {
    return card->suit;
}

void card_show(card_t *card) {
    printf("%d %s\n", card->number, suit_names[card->suit]);
}
