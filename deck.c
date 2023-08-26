#include <stdlib.h>
#include <stdio.h> 

#include "card.h"
#include "deck.h"

#define CARD_QUANTITY 52
#define SUITS_QUANTITY 4
#define NUMBERS_QUATITY 13

struct deck {
    card_t **cards;
    size_t size;
};

deck_t *deck_construct() {
    deck_t *deck = malloc(sizeof(deck_t));
    if (deck == NULL) return NULL;

    deck->cards = malloc(sizeof(card_t *) * CARD_QUANTITY);
    if (deck->cards == NULL) {
        free(deck);
        return NULL;
    }

    deck->size = 0;
    for (size_t suits_count = 0; suits_count < SUITS_QUANTITY; suits_count++) {
        for (size_t numbers_count = 1; numbers_count <= NUMBERS_QUATITY; numbers_count++) {
            if ((deck->cards[deck->size] = card_construct(numbers_count, suits_count)) == NULL) {
                deck_destroy(deck);
                return NULL;
            }
            deck->size++;
        }
    }
    return deck;
}

void deck_destroy(deck_t *deck) {
    size_t card_amount = deck->size + 1;
    for (size_t i = 0; i < card_amount; i++) {
        card_destroy(deck->cards[i]);
    }
    free(deck);
}

void deck_show(deck_t *deck) {
    size_t card_amount = deck->size;
    for(size_t i = 0; i < card_amount; i++)
        card_show(deck->cards[i]);
}
