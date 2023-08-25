#ifndef CARD_H
#define CARD_H

enum suit {
    HEARTS = 0,
    DIAMONDS = 1,
    CLOVERS = 2,
    SPADES = 3
};

typedef enum suit suit_t;
typedef struct card card_t;

card_t *card_construct(unsigned int number, suit_t suit);
void card_destroy(card_t *card);

void card_show(card_t *card);

#endif
