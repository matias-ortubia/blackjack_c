#ifndef DECK_H
#define DECK_H

#include <stdbool.h>
#include "card.h"

typedef struct deck deck_t;

deck_t *deck_construct();
void deck_destroy(deck_t *deck);

card_t *deck_pop(deck_t *deck);
card_t *deck_push(deck_t *deck, card_t *card);
card_t *deck_peek(deck_t *deck);
bool deck_is_empty(deck_t *deck);
void deck_shuffle(deck_t *deck);

void deck_show(deck_t *deck);

#endif
