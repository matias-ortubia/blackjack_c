#include <stdio.h>
#include <stdlib.h>

#include "card.h"

char *suit_names[] = {"Hearts", "Diamonds", "Clovers", "Spades"};

struct card {
    unsigned int number;
    suit_t suit;
};

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

void card_show(card_t *card) {
    printf("%d %s", card->number, suit_names[card->suit]);
}
