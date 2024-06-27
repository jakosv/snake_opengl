#ifndef RECTANGLE_H_SENTRY
#define RECTANGLE_H_SENTRY

#include "shader.h"

typedef struct rectangle_shape {
    unsigned int VAO, VBO, EBO; 
} rectangle_shape_t;

void set_rectangle_coords(int x, int y, int width, int height,
                          int win_width, int win_height,
                          rectangle_shape_t *rect);
void init_rectangle(rectangle_shape_t *rect);
void destroy_rectangle(rectangle_shape_t *rect);
void draw_rectangle(const rectangle_shape_t *rect, shader_t shader);

#endif
