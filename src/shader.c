#include "shader.h"

#include <stdlib.h>
#include <stdio.h>


static void read_shader(const char *filename, char *str, int size)
{
    enum { buflen = 4096 };
    char buf[buflen];
    int res, filled, max_cnt;
    FILE *f;

    f = fopen(filename, "rb");
    if (!f) {
        perror(filename);
        return;
    }

    max_cnt = size - 1;
    filled = 0;
    while (!feof(f) && filled < max_cnt) {
        res = fread(buf, 1, buflen, f);
        if (filled + res >= max_cnt)
            res = max_cnt - filled;
        memcpy(str, buf, res);
        filled += res;
    }

    str[filled] = '\0';

    fclose(f);
}

static void compile_shader(const char *filename, GLenum shader_type,
                           shader_t *shader)
{
    enum { bfs_max_size = 10000 };
    char *buffer_shader_source;
    int success;
    char info_log[512];

    buffer_shader_source = malloc(bfs_max_size);
    read_shader(filename, buffer_shader_source, bfs_max_size);
    /*
    printf("%s", buffer_shader_source);
    */

    *shader = glCreateShader(shader_type);
    glShaderSource(*shader, 1, &buffer_shader_source, NULL);
    glCompileShader(*shader);

    glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(*shader, sizeof(info_log), NULL, info_log);
        fprintf(stderr, "Shader '%s' compilation failed\n", filename);
    }

    free(buffer_shader_source);
}

void shader_init(const char *vertex_shader_filename,
                 const char *fragment_shader_filename,
                 shader_t *shader)
{
    shader_t vertex_shader, fragment_shader;
    int success;
    char info_log[512];

    compile_shader(vertex_shader_filename, GL_VERTEX_SHADER, &vertex_shader);
    compile_shader(fragment_shader_filename, GL_FRAGMENT_SHADER, &fragment_shader);

    *shader = glCreateProgram();
    glAttachShader(*shader, vertex_shader);
    glAttachShader(*shader, fragment_shader);
    glLinkProgram(*shader);

    glGetProgramiv(*shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(*shader, sizeof(info_log), NULL, info_log);
        fprintf(stderr, "Shader program link failed\n");
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void shader_use(shader_t shader)
{
    glUseProgram(shader);
}

void shader_destroy(shader_t shader)
{
    glDeleteProgram(shader);
}

void shader_set_int(const char *name, int value, shader_t shader)
{
    unsigned int location;
    location = glGetUniformLocation(shader, name);
    glUniform1i(location, value);
}

void shader_set_float(const char *name, float value, shader_t shader)
{
    unsigned int location;
    location = glGetUniformLocation(shader, name);
    glUniform1f(location, value);
}

void shader_set_3f(const char *name, float *arr, shader_t shader)
{
    unsigned int location;
    location = glGetUniformLocation(shader, name);
    glUniform3f(location, arr[0], arr[1], arr[2]);
}

void shader_set_4f(const char *name, float *arr, shader_t shader)
{
    unsigned int location;
    location = glGetUniformLocation(shader, name);
    glUniform4f(location, arr[0], arr[1], arr[2], arr[3]);
}
