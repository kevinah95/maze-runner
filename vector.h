#ifndef MAZE_RUNNER_VECTOR_H
#define MAZE_RUNNER_VECTOR_H

#ifndef VECTOR_INITIAL_CAPACITY
#define VECTOR_INITIAL_CAPACITY 100
#endif //VECTOR_INITIAL_CAPACITY

// Define a vector type
typedef struct {
    int size;      // slots used so far
    int capacity;  // total available slots
    char *data;     // array of integers we're storing
} Vector;

void vector_init(Vector *vector);

void vector_append(Vector *vector, char value);

char vector_get(Vector *vector, int index);

void vector_set(Vector *vector, int index, char value);

void vector_double_capacity_if_full(Vector *vector);

void vector_free(Vector *vector);

#endif //MAZE_RUNNER_VECTOR_H