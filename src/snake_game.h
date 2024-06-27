#ifndef SNAKE_GAME_H_SENTRY
#define SNAKE_GAME_H_SENTRY

#include "glad/glad.h"
#include "GLFW/glfw3.h"

void snake_game_init();
void snake_game_free();
int snake_game_score();
void snake_game_start();

#endif
