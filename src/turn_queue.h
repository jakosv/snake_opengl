#ifndef TURN_QUEUE_H_SENTRY
#define TURN_QUEUE_H_SENTRY

struct tq_item {
    int dx, dy;
    struct tq_item *next;
};

typedef struct turn_queue {
    int size;
    struct tq_item *first;
    struct tq_item *last;
} turn_queue_t;

void turn_queue_init(turn_queue_t *tq);
void turn_queue_destroy(turn_queue_t *tq);
void turn_queue_push(int dx, int dy, turn_queue_t *tq);
void turn_queue_pop(int *dx, int *dy, turn_queue_t *tq);
int turn_queue_empty(const turn_queue_t *tq);

#endif
