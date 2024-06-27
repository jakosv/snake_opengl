#ifndef SNAKE_BODY_H_SENTRY
#define SNAKE_BODY_H_SENTRY

#include "shader.h"
#include "field_block.h"

enum { snake_body_size = 50 };

struct snake_body {
    int x, y, dx, dy;
    field_block_t block;
    struct snake_body *next;
};

void snake_body_init(int x, int y, int dx, int dy, shader_t *shader, 
                     struct snake_body *body);
void snake_body_free(struct snake_body *body);
void snake_body_move(struct snake_body *body);
void snake_body_grow(struct snake_body **body, shader_t body_shader);
void snake_body_set_shader(shader_t *shader, struct snake_body *body);

#endif
