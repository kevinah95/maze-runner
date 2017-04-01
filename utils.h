#ifndef MAZE_RUNNER_UTILS_H
#define MAZE_RUNNER_UTILS_H


#include "vector.h"

#define MILLISECOND 1000
#define SECOND 1000*MILLISECOND //1000*MILLISECOND <- One Second

#define PRINTC(c, f, s0) printf ("\033[%dm" f "\033[0m", 30 + c, s0);
#define clear() printf("\033[H\033[J");

unsigned int rand_interval(unsigned int min, unsigned int max);
void gotoxy(int,int);
char get_random_character();
int get_random_int();
void show_maze(const char *maze, int width, int height);
Vector readFile(Vector vector, int *width, int *height);


#endif //MAZE_RUNNER_UTILS_H
