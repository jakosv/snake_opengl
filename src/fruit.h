#ifndef FRUIT_H_SENTRY
#define FRUIT_H_SENTRY

#include "field.h"
#include "field_block.h"

struct fruit {
    int x, y;
    field_block_t block;
};

void fruit_init(int x, int y, struct fruit *fruit);
void fruit_draw(const struct fruit *fruit, const struct field *field);

#endif
