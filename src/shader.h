#ifndef SHADER_H_SENTRY
#define SHADER_H_SENTRY

#include <glad/glad.h>

typedef unsigned int shader_t;

void shader_init(const char *vertex_shader_filename,
                 const char *fragment_shader_filename,
                 shader_t *shader);
void shader_destroy(shader_t shader);
void shader_use(shader_t shader);

void shader_set_int(const char *name, int value, shader_t shader);
void shader_set_float(const char *name, float value, shader_t shader);
void shader_set_3f(const char *name, float *arr, shader_t shader);
void shader_set_4f(const char *name, float *arr, shader_t shader);
#endif
