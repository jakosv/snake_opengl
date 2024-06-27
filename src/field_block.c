#include "field_block.h"

void field_block_init(int width, int height, shader_t *shader,
                      field_block_t *block)
{
    block->width = width;
    block->height = height;
    block->shader = *shader;
    init_rectangle(&block->block_shape);
}

void field_block_destroy(field_block_t *block)
{
    destroy_rectangle(&block->block_shape);
}

void field_block_draw(int x, int y, const field_block_t *block,
                      int win_width, int win_height)
{
    set_rectangle_coords(x, y, block->width, block->height,
                         win_width, win_height, &block->block_shape);
    shader_use(block->shader);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void field_block_set_shader(field_block_t *block, shader_t *shader)
{
    block->shader = *shader;
}
