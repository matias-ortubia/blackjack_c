#include <stdio.h>

#include "card.h"

int main(void) {
    card_t *card = card_construct(7, HEARTS);

    card_show(card);
    printf("%d\n", card_get_number(card));

    printf("%s\n", suit_names[card_get_suit(card)]);

    card_destroy(card);
    return 0;
}
