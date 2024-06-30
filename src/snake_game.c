#include "snake_game.h"
#include "field.h"
#include "snake.h"
#include "snake_body.h"
#include "fruit.h"
#include "turn_queue.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <stdlib.h>
#include <stdio.h>


struct snake_game {
    struct field *field;
    struct snake *snake;
    struct fruit *fruit;
    int win_width, win_height;
    double snake_speed;
    double last_move_time;
    GLFWwindow *window;
    int score, score_msg_x, score_msg_y;
    int game_over;
    turn_queue_t turns;
};


enum { init_win_width = 800, init_win_height = 600 };
enum { field_width = 600, field_height = 400 };
enum { key_escape = 27 };

const double snake_init_speed = 3; 
const double snake_speed_grow = 0.2;

struct snake_game *game;

static int rand_int(int low, int hight)
{
    return low + (int)(1.0*hight*rand()/(RAND_MAX+1.0));
}

static void add_snake()
{
    int x, y, dx, dy;
    x = rand_int(2, game->field->width / snake_body_size - 3);
    x *= snake_body_size;
    y = rand_int(2, game->field->height / snake_body_size - 3);
    y *= snake_body_size;
    dx = rand_int(-1, 1);
    if (dx == 0)
        dy = rand_int(0, 1) == 0 ? 1 : -1;
    else
        dy = 0;
    game->snake = malloc(sizeof(struct snake));
    snake_init(x, y, dx, dy, game->snake);
}

static void add_fruit()
{
    int x, y;
    do {
        x = rand_int(0, game->field->width/snake_body_size-1);
        y = rand_int(0, game->field->height/snake_body_size-1);
        x *= snake_body_size;
        y *= snake_body_size;
    } while (game->snake && is_snake_tail(x, y, game->snake));

    game->fruit = malloc(sizeof(struct fruit));
    fruit_init(x, y, game->fruit);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    game->win_width = width;
    game->win_height = height;
    glViewport(0, 0, width, height);
}

static int check_snake_fruit_collision(const struct fruit *fruit, 
                                       const struct snake *snake)
{
    int snake_x, snake_y;
    snake_x = snake->head->x + snake->head->dx;
    snake_y = snake->head->y + snake->head->dy;
    return snake_x == fruit->x && snake_y == fruit->y;
}

static void handle_snake_fruit_collision()
{
    free(game->fruit);
    snake_eat_fruit(game->snake, game->field);
    add_fruit();
    fruit_draw(game->fruit, game->field);
    game->score++;
    game->snake_speed += snake_speed_grow;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key) {
    case GLFW_KEY_UP:
        turn_queue_push(0, -1, &game->turns);
        break;
    case GLFW_KEY_DOWN:
        turn_queue_push(0, 1, &game->turns);
        break;
    case GLFW_KEY_LEFT:
        turn_queue_push(-1, 0, &game->turns);
        break;
    case GLFW_KEY_RIGHT:
        turn_queue_push(1, 0, &game->turns);
        break;
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, 1);
        return;
    } 
}

void opengl_init()
{
    int res;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    game = malloc(sizeof(struct snake_game));
    game->window = glfwCreateWindow(init_win_width, init_win_height,
                                    "Snake Game", NULL, NULL);
    if (game->window == NULL) {
        fprintf(stderr, "Failed to create GLFW window\n");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(game->window);

    res = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    if (!res) {
        fprintf(stderr, "Failed to init glad\n");
        return;
    }

    glViewport(0, 0, init_win_width, init_win_height);

    glfwSetFramebufferSizeCallback(game->window, framebuffer_size_callback);
    
    glfwSetKeyCallback(game->window, key_callback);
}

void snake_game_init()
{
    int field_x, field_y;

    opengl_init();

    field_x = (init_win_width - field_width) / 2;
    field_y = (init_win_height - field_height) / 2;

    game->win_width = init_win_width;
    game->win_height = init_win_height;
    game->snake_speed = snake_init_speed;
    game->last_move_time = 0;
    game->score = 0;
    game->game_over = 0;
    game->field = field_create(field_x, field_y, field_width, field_height,
                               game->win_width, game->win_height);
    turn_queue_init(&game->turns);
    add_snake(game);
    add_fruit(game);
}

static void game_draw()
{
    field_draw(game->field);
    snake_draw(game->snake, game->field);
    fruit_draw(game->fruit, game->field); 
}

void snake_game_free()
{
    snake_free(game->snake);
    free(game->snake);
    free(game->fruit);
    free(game->field);
    turn_queue_destroy(&game->turns);
    game->snake = NULL;
    game->fruit = NULL;
    game->field = NULL;

    glfwTerminate();
    free(game);
}

void snake_game_start()
{
    while (!glfwWindowShouldClose(game->window) && !game->game_over) {
        double now, snake_path;

        glClearColor(0.2f, 0.3f, 0.3f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT);

        game_draw();

        now = glfwGetTime();
        snake_path = game->snake_speed * (now - game->last_move_time);
        if (snake_path >= 1.0) {
            while (!turn_queue_empty(&game->turns)) {
                int dx, dy;
                turn_queue_pop(&dx, &dy, &game->turns);
                if (is_snake_correct_direction(dx, dy, game->snake)) {
                    snake_set_direction(dx, dy, game->snake);
                    break;
                }
            }
            if (check_snake_fruit_collision(game->fruit, game->snake))
                handle_snake_fruit_collision();
            else if (check_snake_tail_collision(game->snake))
                game->game_over = 1;
            else
                snake_move(game->snake, game->field); 

            game->last_move_time = now;
        }

        glfwSwapBuffers(game->window);
        glfwPollEvents();
    }
}

int snake_game_score()
{
    return game->score;
}
