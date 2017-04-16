#ifndef MAZE_RUNNER_THREAD_H
#define MAZE_RUNNER_THREAD_H

#include <stdio.h>

struct Data;

enum Direction {UP,RIGHT,DOWN,LEFT};

typedef struct Data
{
    int future_x_pos;
    int future_y_pos;
    int accumulated_movements;
    enum Direction future_direction;
    int drawed;
} ThreadData;


typedef struct {
    ThreadData *array;
    size_t size;
    size_t mem_size;
} Array;

void initArray(Array *a, size_t initialSize);
void insertArray(Array *a, ThreadData *element);
void freeArray(Array *a);
void print_in_maze(ThreadData *p_data);
void print_in_coordinates(int x, int y, char *to_print);
void reverse_loop_immutable_coord_x(int start_y_pos,int end_y_pos, int is_reverse, int immutable_coord_x, char *to_print);
void reverse_loop_immutable_coord_y(int start_x_pos,int end_x_pos, int is_reverse, int immutable_coord_y, char *to_print);


#endif //MAZE_RUNNER_THREAD_H
