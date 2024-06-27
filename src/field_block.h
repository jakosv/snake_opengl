#ifndef FIELD_BLOCK_H_SENTRY
#define FIELD_BLOCK_H_SENTRY

#include "shader.h"
#include "rectangle.h"

typedef struct field_block {
    int width, height;
    rectangle_shape_t block_shape;
    shader_t shader;
} field_block_t;

void field_block_init(int width, int height, shader_t *shader,
                      field_block_t *block);
void field_block_draw(int x, int y, const field_block_t *block,
                      int win_width, int win_height);
void field_block_set_shader(field_block_t *block, shader_t *shader);

#endif
