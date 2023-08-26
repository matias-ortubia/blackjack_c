#ifndef DECK_H
#define DECK_H

typedef struct deck deck_t;

deck_t *deck_construct();
void deck_destroy(deck_t *deck);

void deck_show(deck_t *deck);

/* 
 * push
 * pop
 * peek
 * is_empty
 * shuffle
 *
 * */

#endif
