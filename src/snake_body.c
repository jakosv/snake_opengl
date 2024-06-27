#include "snake_body.h"
#include "field_block.h"

#include <stdlib.h>

void snake_body_init(int x, int y, int dx, int dy, shader_t *shader, 
                     struct snake_body *body)
{
    body->x = x;
    body->y = y;
    body->dx = dx;
    body->dy = dy;
    field_block_init(snake_body_size, snake_body_size, shader, &body->block);
    body->next = NULL;
}

void snake_body_free(struct snake_body *body)
{
    struct snake_body *tmp;
    while (body) {
        tmp = body;
        body = body->next;
        free(tmp);
    }
}

void snake_body_move(struct snake_body *body)
{
    body->x += body->dx;
    body->y += body->dy;
}

void snake_body_grow(struct snake_body **body, shader_t body_shader)
{
    int new_body_x, new_body_y, dx, dy;
    struct snake_body *new_body;
    new_body = malloc(sizeof(struct snake_body));
    dx = (*body)->dx;
    dy = (*body)->dy;
    new_body_x = (*body)->x + dx;
    new_body_y = (*body)->y + dy;
    snake_body_init(new_body_x, new_body_y, dx, dy, &(*body)->block.shader,
                    new_body);
    field_block_set_shader(&(*body)->block, &body_shader);
    new_body->next = *body;
    *body = new_body;
}

void snake_body_set_shader(shader_t *shader, struct snake_body *body)
{
    body->block.shader = *shader;
}
