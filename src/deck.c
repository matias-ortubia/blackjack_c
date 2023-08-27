#include <stdlib.h>
#include <time.h>
#include <stdio.h> 

#include "../inc/card.h"
#include "../inc/deck.h"

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
    size_t card_amount = deck->size;
    for (size_t i = 0; i < card_amount; i++) {
        card_destroy(deck->cards[i]);
    }
    free(deck);
}

card_t *deck_pop(deck_t *deck) {
    if (deck->size == 0) return NULL;

    deck->size--;
    
    card_t *card = deck->cards[deck->size];

    card_t **temp = realloc(deck->cards, sizeof(card_t *) * deck->size);
    if (temp == NULL) return NULL;
    deck->cards = temp;

    return card;
}

card_t *deck_push(deck_t *deck, card_t *card) {
    deck->size++;
    card_t **temp = realloc(deck->cards, sizeof(card_t *) * deck->size);
    if (temp == NULL) return NULL;

    deck->cards = temp;
    deck->cards[deck->size - 1] = card;

    return card;
}

card_t *deck_peek(deck_t *deck) {
    return deck->cards[deck->size -1];
}

bool deck_is_empty(deck_t *deck) {
    return deck->size == 0;
}

void deck_shuffle(deck_t *deck) {
    srand(time(NULL));
    size_t size = deck->size;
    size_t max_iteration = size - 1;
    for (size_t i = 0; i < max_iteration; i++) {
        size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
        card_t *aux = deck->cards[j];
        deck->cards[j] = deck->cards[i];
        deck->cards[i] = aux;
    }
}

void deck_show(deck_t *deck) {
    size_t card_amount = deck->size;
    for(size_t i = 0; i < card_amount; i++)
        card_show(deck->cards[i]);
}
