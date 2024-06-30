#include "turn_queue.h"

#include <stdlib.h>

void turn_queue_init(turn_queue_t *tq)
{
    tq->first = NULL;
    tq->last = NULL;
    tq->size = 0;
}

void turn_queue_destroy(turn_queue_t *tq)
{
    struct tq_item *tmp;
    while (tq->first) {
       tmp = tq->first;
       tq->first = tq->first->next;
       free(tmp);
    }
    tq->first = NULL;
    tq->last = NULL;
    tq->size = 0;
}

void turn_queue_push(int dx, int dy, turn_queue_t *tq)
{
    if (!tq->first) {
        tq->last = malloc(sizeof(struct tq_item));
        tq->first = tq->last;
    } else {
        tq->last->next = malloc(sizeof(struct tq_item));
        tq->last = tq->last->next;
    }
    tq->last->dx = dx;
    tq->last->dy = dy;
    tq->last->next = NULL;
    tq->size += 1;
}

void turn_queue_pop(int *dx, int *dy, turn_queue_t *tq)
{
    struct tq_item *tmp;
    *dx = tq->first->dx;
    *dy = tq->first->dy;
    tmp = tq->first;
    tq->first = tq->first->next;
    free(tmp);
    tq->size -= 1;
}

int turn_queue_empty(const turn_queue_t *tq)
{
    return tq->size == 0;
}
