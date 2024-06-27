#include "snake_game.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main()
{
    srand(time(NULL));
    snake_game_init();
    snake_game_start();
    printf("Score: %d\n", snake_game_score());
    snake_game_free();

    return 0;
}
