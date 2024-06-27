#include "rectangle.h"

#include <glad/glad.h>

typedef float (*vertex_coords_arr_ptr)[3];

const unsigned int indices[] = {
    0, 1, 2, /* first triangle */
    1, 2, 3  /* second triangle */
};

static void init_rectangle_vertices(int x, int y, int width, int height,
                                    vertex_coords_arr_ptr border_vertices)
{
    int right_corner_x, bottom_corner_y;
    right_corner_x = x + width - 1;
    bottom_corner_y = y + height - 1; 

    /* top left vertex */
    border_vertices[0][0] = x;
    border_vertices[0][1] = y;
    border_vertices[0][2] = 0;

    /* top right vertex */
    border_vertices[1][0] = right_corner_x;
    border_vertices[1][1] = y;
    border_vertices[1][2] = 0;

    /* botoom left vertex */
    border_vertices[2][0] = x;
    border_vertices[2][1] = bottom_corner_y;
    border_vertices[2][2] = 0;

    /* bottom right vertex */
    border_vertices[3][0] = right_corner_x;
    border_vertices[3][1] = bottom_corner_y;
    border_vertices[3][2] = 0;
}

static void normalize_rectangle_coords(int win_width, int win_height,
                                       vertex_coords_arr_ptr border_vertices)
{
    int i;
    for (i = 0; i < 4; i++) {
        border_vertices[i][0] = border_vertices[i][0] * 2 / win_width - 1;
        border_vertices[i][1] = -border_vertices[i][1] * 2 / win_height + 1;
    }
}

void set_rectangle_coords(int x, int y, int width, int height,
                          int win_width, int win_height,
                          rectangle_shape_t *rect)
{
    float vertices[4][3];

    init_rectangle_vertices(x, y, width, height, vertices);
    normalize_rectangle_coords(win_width, win_height, vertices);

    glBindVertexArray(rect->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, rect->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rect->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, 
                 GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float),
                          (void *)0);
    glEnableVertexAttribArray(0);
}

void init_rectangle(rectangle_shape_t *rect)
{
    glGenVertexArrays(1, &rect->VAO);
    glGenBuffers(1, &rect->VBO);
    glGenBuffers(1, &rect->EBO);
}

void destroy_rectangle(rectangle_shape_t *rect)
{
    glDeleteVertexArrays(1, &rect->VAO);
    glDeleteBuffers(1, &rect->VBO);
    glDeleteBuffers(1, &rect->EBO);
}

void draw_rectangle(const rectangle_shape_t *rect, shader_t shader)
{
    shader_use(shader);
    glBindVertexArray(rect->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
