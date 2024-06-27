#include "snake.h"
#include "snake_body.h"
#include "utils.h"
#include "shader.h"

#include <stdlib.h>

MAKE_SWAP_FUNCTION(int)

void snake_init(int x, int y, int dx, int dy, struct snake *snake)
{
    shader_init("shaders/snake_body.vs", "shaders/snake_body.fs", 
                &snake->body_shader);
    shader_init("shaders/snake_head.vs", "shaders/snake_head.fs",
                &snake->head_shader);
    snake->head = malloc(sizeof(struct snake_body));
    dx *= snake_step;
    dy *= snake_step;
    snake_body_init(x, y, dx, dy, &snake->head_shader, snake->head);
}

void snake_free(struct snake *snake)
{
    snake_body_free(snake->head);
    snake->head = NULL;
}

static void snake_body_draw(const struct snake_body *body,
                            const struct field *field)
{
    field_draw_block(body->x, body->y, &body->block, field);
}

void snake_draw(const struct snake *snake, const struct field *field)
{
    struct snake_body *tmp;
    for (tmp = snake->head; tmp; tmp = tmp->next)
        snake_body_draw(tmp, field);
}

static void check_coord(int *coord, int max_coord)
{
    if (*coord + snake_body_size - 1 > max_coord)
       *coord = 0;
    else if (*coord < 0)
       *coord = max_coord - snake_body_size + 1;
}

static void update_body_direction(int *dx, int *dy, struct snake_body *body)
{
    if (body->dx != *dx || body->dy != *dy) {
        swap_int(&body->dx, dx);
        swap_int(&body->dy, dy);
    }
}

static int is_correct_direction(int dx, int dy, const struct snake *snake)
{
    /*
    return (snake->head->dx * dx + snake->head->dy * dy) == 0;
    */
    return !is_snake_tail(snake->head->x + dx, snake->head->y + dy, snake);
}

void snake_move(struct snake *snake, const struct field *field)
{
    struct snake_body *tmp;
    int body_dx, body_dy;
    body_dx = snake->head->dx;
    body_dy = snake->head->dy;
    for (tmp = snake->head; tmp; tmp = tmp->next) {
        snake_body_move(tmp);
        check_coord(&tmp->x, field->width - 1);
        check_coord(&tmp->y, field->height - 1);
        if (tmp != snake->head)
            update_body_direction(&body_dx, &body_dy, tmp);
    }
}

void snake_eat_fruit(struct snake *snake, const struct field *field)
{
    snake_body_grow(&snake->head, snake->body_shader);
}

int is_snake_tail(int x, int y, const struct snake *snake)
{
    struct snake_body *tmp;
    for (tmp = snake->head; tmp; tmp = tmp->next)
        if (tmp->x == x && tmp->y == y)
            return 1;
    return 0;
}

int check_snake_tail_collision(const struct snake *snake)
{
    int snake_x, snake_y;
    snake_x = snake->head->x + snake->head->dx;
    snake_y = snake->head->y + snake->head->dy;
    return is_snake_tail(snake_x, snake_y, snake);
}

void snake_set_direction(int dx, int dy, struct snake *snake)
{
    int snake_dx, snake_dy;
    snake_dx = dx * snake_step;
    snake_dy = dy * snake_step;
    if (!is_correct_direction(snake_dx, snake_dy, snake))
        return;
    snake->head->dx = snake_dx;
    snake->head->dy = snake_dy;
}
