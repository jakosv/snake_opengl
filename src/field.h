#ifndef FIELD_H_SENTRY
#define FIELD_H_SENTRY

#include "shader.h"
#include "field_block.h"

typedef struct field {
    int x, y;
    int width, height;
    int win_width, win_height;
    shader_t field_shader, border_shader;
    rectangle_shape_t field_shape, border_shape;
} field_t;

field_t *field_create(int x, int y, int width, int height, 
                      int win_width, int win_height);
void field_draw(const field_t *field);
void field_draw_block(int x, int y, const field_block_t *block, const field_t *field);

#endif
