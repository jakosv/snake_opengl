#include "field.h"
#include "rectangle.h"

#include <stdlib.h>

typedef float (*border_vertex_ptr)[3];

enum { border_size = 10 };

static void init_border_vertices_buffer(field_t *field)
{
    int startx, starty, border_width, border_height;
    startx = field->x - border_size;
    starty = field->y - border_size;
    border_width = field->width + border_size * 2;
    border_height = field->height + border_size * 2;
    init_rectangle(&field->border_shape);
    set_rectangle_coords(startx, starty, border_width, border_height,
                         field->win_width, field->win_height, 
                         &field->border_shape);
}

field_t *field_create(int x, int y, int width, int height, 
                      int win_width, int win_height)
{
    field_t *field;
    field = malloc(sizeof(field_t));
    field->x = x;
    field->y = y;
    field->width = width;
    field->height = height;
    field->win_width = win_width;
    field->win_height = win_height;

    shader_init("shaders/field_border.vs", "shaders/field_border.fs",
                &field->border_shader);
    shader_init("shaders/field.vs", "shaders/field.fs", &field->field_shader);
    init_border_vertices_buffer(field);
    init_rectangle(&field->field_shape);
    set_rectangle_coords(x, y, width, height, win_width, win_height, 
                         &field->field_shape);

    return field;
}

void field_destroy(field_t *field)
{
    destroy_rectangle(&field->border_shape);
    destroy_rectangle(&field->field_shape);
    shader_destroy(field->border_shader);
    shader_destroy(field->field_shader);
}

void field_draw(const field_t *field)
{
    draw_rectangle(&field->border_shape, field->border_shader);
    draw_rectangle(&field->field_shape, field->field_shader);
}

void field_draw_block(int x, int y, const field_block_t *block,
                      const field_t *field)
{
    field_block_draw(field->x + x, field->y + y, block,
                     field->win_width, field->win_height);
}
