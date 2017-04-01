#ifndef MAZE_RUNNER_THREAD_H
#define MAZE_RUNNER_THREAD_H



struct Data;

typedef struct Data
{
    int future_x_pos;
    int future_y_pos;
    int accumulated_movements;
    int future_direction;
    int drawed;
} ThreadData;


typedef struct {
    ThreadData *array;
    size_t used;
    size_t size;
} Array;

void initArray(Array *a, size_t initialSize);
void insertArray(Array *a, ThreadData *element);
void freeArray(Array *a);



#endif //MAZE_RUNNER_THREAD_H
