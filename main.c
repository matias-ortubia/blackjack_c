#include <stdio.h>

#include "card.h"

int main(void) {
    card_t *card = card_construct(7, HEARTS);

    card_show(card);

    card_destroy(card);
    return 0;
}
