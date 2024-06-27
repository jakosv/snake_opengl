#include "fruit.h"

void fruit_init(int x, int y, struct fruit *fruit)
{
    shader_t fruit_shader;
    fruit->x = x;
    fruit->y = y;
    shader_init("shaders/fruit.vs", "shaders/fruit.fs", &fruit_shader);
    field_block_init(50, 50, &fruit_shader, &fruit->block);
}

void fruit_draw(const struct fruit *fruit, const struct field *field)
{
    field_draw_block(fruit->x, fruit->y, &fruit->block, field);
}
